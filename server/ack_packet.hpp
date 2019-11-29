#ifndef MATCHMAKING_ACK_PACKET_HPP
#define MATCHMAKING_ACK_PACKET_HPP

#include <string>
#include <nlohmann/json.hpp>

#include "packet.hpp"
#include "ack_type.hpp"

namespace Matchmaking
{

class AckPacket : public Packet
{
public:
  enum { header_length = 8 };
  enum { max_body_length = 512 };

  AckPacket();

  AckPacket(AckType ack_type);

  AckType get_ack_type();

  bool encode();

  bool decode_body();

protected:
  AckType ack_type_;
};

}

#endif // MATCHMAKING_ACK_PACKET_HPP
