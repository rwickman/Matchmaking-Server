#ifndef MATCHMAKING_PACKET_HPP
#define MATCHMAKING_PACKET_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Matchmaking
{

class Packet
{
public:
  enum { header_length = 4 };
  enum { max_body_length = 512 };

  Packet();
  
  char* data();

  char* body();

  std::size_t length();
  
  void body_length(std::size_t new_length);
  
  void encode_header();
  
  bool decode_header();


protected:
  //const uint16_t header_length_;
  //const std::size_t max_body_length_;
  std::size_t body_length_;
  char data_[header_length + max_body_length];
};

}
#endif // MATCHMAKING_PACKET_HPP
