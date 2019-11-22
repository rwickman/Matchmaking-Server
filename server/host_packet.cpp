#include "host_packet.hpp"

namespace Matchmaking
{
  HostPacket::HostPacket()
  : Packet(PacketType::Host)
  {
  }

  HostPacket::HostPacket(GameType game_type)
  : Packet(PacketType::Host)
  , game_type_(game_type)
  {
  }


  GameType HostPacket::get_game_type()
  {
    return game_type__;
  }

  bool HostPacket::encode_body()
  {
    try
    {
      nlohmann::json host_json;
      host_json["Packet Type"] = (int) packet_type_;
      host_json["Game Type"] = game_type_;
      std::string host_str(host_json.dump());
      host_str.copy(body(), host_str.size());
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }

  bool HostPacket::decode_body()
  {
    try
    {
      nlohmann::json host_json = nlohmann::json::parse(body());
      game_type__ = static_cast<GameType>(host_json["Game Type"].get<int>());
      //packet_type_ = host_json["Packet Type"].get<PacketType>();
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }

}

