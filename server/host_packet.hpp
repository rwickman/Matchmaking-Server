#ifndef MATCHMAKING_HOST_PACKET_HPP
#define MATCHMAKING_HOST_PACKET_HPP

#include <string>
#include <nlohmann/json.hpp>

#include "packet.hpp"
#include "game_type.hpp"

namespace Matchmaking
{

class HostPacket : public Packet
{
public:
  enum { header_length = 8 };
  enum { max_body_length = 512 };

  HostPacket();

  HostPacket(GameType game_type);

  GameType get_game_type();

  bool encode_body();

  bool decode_body();

protected:
  GameType game_type_;
};

}

#endif // MATCHMAKING_HOST_PACKET_HPP
