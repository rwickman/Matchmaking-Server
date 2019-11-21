#include "packet.hpp"

namespace Matchmaking
{
  Packet::Packet()
  : body_length_(0)
  , packet_type_(Packet)
  {
  }

  Packet::Packet(PacketType packet_type)
  : body_length_(0)
  , packet_type_(packet_type)
  {
  }

  char* Packet::data()
  {
    return data_;
  }

  char* Packet::body()
  {
    return data_ + header_length;
  }

  std::size_t Packet::length()
  {
    return header_length + body_length_;
  }

  std::size_t Packet::body_length()
  {
    return body_length_;
  }

  PacketType Packet::packet_type()
  {
    return packet_type_;
  }

  void Packet::set_body_length(std::size_t new_length)
  {
    body_length_ = new_length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
  }

  void Packet::encode_header()
  {
    char header[header_length + 1] = "";
    // write formated string to header
    sprintf(header, "%4d", body_length_);
    // Copy block of memory
    memcpy(data_, header, header_length);
  }

  bool Packet::decode_header()
  {
    char header[header_length + 1] = "";
    strncat(header, data_, header_length);
    body_length_ = atoi(header);
    if (body_length_ > max_body_length)
    {
      body_length_ = 0;
      return false;
    }
    return true;
  }
}
