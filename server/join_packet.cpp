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

  bool JoinPacket::encode_body()
  {
    try
    {
      nlohmann::json join_json;
      join_json["Packet Type"] = (int) packet_type_;
      join_json["IP"] = ip_address_;
      join_json["PID"] = pid_;
      std::string join_str(join_json.dump());
      set_body_length(join_str.size());
      join_str.copy(body(), join_str.size());
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }


  bool JoinPacket::decode_body()
  {
    try
    {
      nlohmann::json join_json = nlohmann::json::parse(body());
      // In the future consider doing some authentication of User ID
      ip_address_ = join_json["IP"].get<std::string>();
      pid_ = join_json["PID"].get<std::string>();
      //packet_type_ = join_json["Packet Type"].get<PacketType>();
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }

}

