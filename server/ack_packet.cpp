#include "ack_packet.hpp"

namespace Matchmaking
{ 
  AckPacket::AckPacket()
  : Packet(PacketType::Ack)
  {
  }

  AckPacket::AckPacket(AckType ack_type)
  : Packet(PacketType::Ack)
  , ack_type_(ack_type)
  {
  }

  AckType AckPacket::get_ack_type()
  {
    return  ack_type_;
  }

  bool AckPacket::encode()
  {
    try
    {
      nlohmann::json ack_json;
      ack_json["ackType"] = (int)ack_type_;
      std::string ack_str(ack_json.dump());
      set_body_length(ack_str.size());
      encode_header();
      ack_str.copy(body(), ack_str.size());
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }

  bool AckPacket::decode_body()
  {
    try
    {
      nlohmann::json ack_json = nlohmann::json::parse(body());
      ack_type_ = static_cast<AckType>(ack_json["ackType"].get<int>());
      //packet_type_ = ack_json["packetType"].get<PacketType>();
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }

}

