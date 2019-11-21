#include "join_packet.hpp"

namespace Matchmaking
{
  JoinPacket::JoinPacket()
  : Packet(PacketType::Join)
  {
  } 
  
  JoinPacket::JoinPacket(std::string ip_address, std::string pid)
  : Packet(PacketType::Join)
  , ip_address_(ip_address)
  , pid_(pid)
  {
  }
  
  std::string JoinPacket::get_ip_address()
  {
    return ip_address_;
  }

  std::string JoinPacket::get_pid()
  {
    return pid_;
  }

  bool JoinPacket::decode_join()
  {
    try
    {
      nlohmann::json join_json = nlohmann::json::parse(body());
      // In the future consider doing some authentication of User ID
      ip_address_ = join_json["IP"].get<std::string>();
      pid_ = join_json["PID"].get<std::string>();
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }

}

