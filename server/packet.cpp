#include "packet.hpp"

namespace Matchmaking
{
  Packet::Packet() : 
	  body_length_(0)
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

  void Packet::body_length(std::size_t new_length)
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
