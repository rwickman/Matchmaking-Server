#ifndef MATCHMAKING_JOIN_PACKET_HPP
#define MATCHMAKING_JOIN_PACKET_HPP


#include <string>
#include <nlohmann/json.hpp>

#include "packet.hpp"
#include "game_type.hpp"

namespace Matchmaking
{

class JoinPacket : public Packet
{
public:
  enum { header_length = 8 };
  enum { max_body_length = 512 };

  JoinPacket();

  std::string get_ip_address();

  std::string get_pid();
  
  bool decode_join();

protected:
  std::string ip_address_;
  std::string pid_;

};

}

#endif // MATCHMAKING_JOIN_PACKET_HPP

