#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include "server/find_game_packet.hpp"
#include "server/join_packet.hpp"
#include "server/host_packet.hpp"
#include "server/packet.hpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
 try
  {
    if (argc < 3)
    {
      std::cerr << "Usage: client <host> <user_id> <game_type>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "12001");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    
    nlohmann::json j;
    j["User ID"] =  argv[2];
    j["Game Type"] = std::stoi(argv[3]);
    
    
    std::string j_str = j.dump();

    Matchmaking::FindGamePacket find_game_packet;

    
    // Encode the header to the correct body length
    find_game_packet.set_body_length(j_str.size());
    find_game_packet.encode_header();

    // Send the find_game packet
    size_t bytes_written = socket.write_some(boost::asio::buffer(find_game_packet.data(), find_game_packet.header_length));
    std::cout << bytes_written << std::endl;

    // Copy into find_game packet
    j_str.copy(find_game_packet.body(), j_str.size());
    std::string temp(find_game_packet.body());
    bytes_written = socket.write_some(boost::asio::buffer(find_game_packet.body(), find_game_packet.body_length()));
    std::cout << bytes_written << std::endl;


    std::cin.ignore();
    
    char packet_length[find_game_packet.header_length];
    size_t bytes_read =  socket.read_some(boost::asio::buffer(packet_length, find_game_packet.header_length));
    size_t data_length = std::stoi(packet_length);
    
    char packet_data[data_length];
    socket.read_some(boost::asio::buffer(packet_data, data_length));
    std::string packet_str(packet_data, data_length);
    nlohmann::json packet_json =  nlohmann::json::parse(packet_str);

    int packet_type = packet_json["Packet Type"].get<int>();
    if (packet_type == 3)
    {
      // Create join packet and send to all users
      Matchmaking::JoinPacket join_packet("localhost", "12000");
      join_packet.encode();
      std::cout.write(join_packet.data(), join_packet.header_length);
      std::cout << std::endl;
      std::cout.write(join_packet.data(), join_packet.body_length());
      socket.write_some(boost::asio::buffer(join_packet.data(), join_packet.length()));
    }
    else if (packet_type == 2)
    {
      // Join other persons game
      std::cout << "Joining Game: " << packet_json["IP"].get<std::string>() << ":" << packet_json["PID"].get<std::string>();
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
