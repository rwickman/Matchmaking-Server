#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
 try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    
    nlohmann::json j;
    j["User ID"] = "123456";
    j["Game Type"] = 0;
    std::cout << sizeof(j.dump()) << std::endl;
    
    for (;;)
    {
      //boost::array<char, 128> buf;
      boost::system::error_code error;
      size_t bytes_written = socket.write_some(boost::asio::buffer(j.dump()));
      //size_t len = socket.read_some(boost::asio::buffer(buf), error);

/*
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
  */    
      //std::string server_str(buf.data(), len);
      //nlohmann::json server_rsp = nlohmann::json::parse(server_str);
      //std::string ip = server_rsp["IP"].get<std::string>();
      //std::cout << "localhost" << std::endl;
      //std::cout << ip << std::endl;
      //std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
