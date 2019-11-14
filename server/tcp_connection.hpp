#ifndef MATCHMAKING_TCP_CONNECTION_HPP
#define MATCHMAKING_TCP_CONNECTION_HPP

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace Matchmaking
{

using boost::asio::ip::tcp;

class TCPConnection
  : public boost::enable_shared_from_this<TCPConnection>
{
public:
  typedef boost::shared_ptr<TCPConnection> pointer;

  static pointer create(boost::asio::io_context& io_context);

  tcp::socket& socket();

  void start();

private:
  TCPConnection(boost::asio::io_context& io_context); 

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/);

  tcp::socket socket_;
  std::string message_;
};

}
#endif // MATCHMAKING_TCP_CONNECTION_HPP
