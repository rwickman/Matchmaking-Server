#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

#include "server/find_game_packet.hpp"

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
    
    
    std::string j_st = j.dump();
    const char* j_str = j_st.c_str();

    Matchmaking::FindGamePacket find_game_packet;

    
    // Encode the header to the correct body length
    find_game_packet.set_body_length(j_st.size());
    find_game_packet.encode_header();

    // Send the find_game packet
    size_t bytes_written = socket.write_some(boost::asio::buffer(find_game_packet.data(), find_game_packet.header_length));
    std::cout << bytes_written << std::endl;

    // Copy into find_game packet
    memcpy(find_game_packet.body(), j_str, j_st.size());
    std::string temp(find_game_packet.body());
    std::cout << "BODY: " << find_game_packet.body() << std::endl;
    
    bytes_written = socket.write_some(boost::asio::buffer(find_game_packet.body(), find_game_packet.body_length()));
    std::cout << bytes_written << std::endl;
  /* 
    for (;;)
    {
      //boost::array<char, 128> buf;
      //size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
      //std::string server_str(buf.data(), len);
      //nlohmann::json server_rsp = nlohmann::json::parse(server_str);
      //std::string ip = server_rsp["IP"].get<std::string>();
      //std::cout << "localhost" << std::endl;
      //std::cout << ip << std::endl;
      //std::cout.write(buf.data(), len);
    }
  */
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
