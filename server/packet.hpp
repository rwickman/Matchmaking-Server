#ifndef MATCHMAKING_PACKET_HPP
#define MATCHMAKING_PACKET_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "packet_type.hpp"

namespace Matchmaking
{

class Packet
{
public:
  enum { header_length = 8 };
  enum { max_body_length = 512 };

  Packet();
  
  Packet(PacketType packet_type);
  
  char* data();

  char* body();

  std::size_t length();
   
  std::size_t body_length();

  PacketType packet_type();

  void set_body_length(std::size_t new_length);
  
  void encode_header();
  
  bool decode_header();

  virtual bool encode() = 0;
  
  virtual bool decode_body() = 0;

protected:
  //const uint16_t header_length_;
  //const std::size_t max_body_length_;
  std::size_t body_length_;
  char data_[header_length + max_body_length];
  PacketType packet_type_;

};

}
#endif // MATCHMAKING_PACKET_HPP
