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

  std::string get_ip_address();

  std::string get_game_type();

  bool decode_host();

protected:
  std::string ip_address_;
  GameType game_type;

};

}

#endif // MATCHMAKING_HOST_PACKET_HPP
