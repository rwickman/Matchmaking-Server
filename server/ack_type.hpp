#ifndef MATCHMAKING_ACK_TYPE_HPP
#define MATCHMAKING_ACK_TYPE_HPP

#include <exception>

class ack_error : public std::exception
{
public:
  const char* what() const throw()
  {
    return "Ack error!";
  }
};

enum AckType {
  None,
  Error
};

#endif // MATCHMAKING_ACK_TYPE_HPP
