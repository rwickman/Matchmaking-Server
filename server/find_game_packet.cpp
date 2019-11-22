#include "find_game_packet.hpp"

namespace Matchmaking
{
  FindGamePacket::FindGamePacket()
  : Packet(PacketType::FindGame)
  {
  }

  std::string FindGamePacket::get_user_id()
  {
    return user_id_;
  }

  GameType FindGamePacket::get_game_type()
  {
    return game_type_;
  }

  bool FindGamePacket::encode_body()
  {
    try
    {
      nlohmann::json find_game_json;
      find_game_json["Packet Type"] = (int) packet_type_;
      find_game_json["User ID"] = user_id_; 
      find_game_json["Game Type"] = game_type_;
      std::string find_game_str(find_game_json.dump());
      set_body_length(find_game_str.size());
      find_game_str.copy(body(), find_game_str.size());
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }

  bool FindGamePacket::decode_body()
  {
    try
    {
      nlohmann::json find_game_json = nlohmann::json::parse(body());
      // In the future consider doing some authentication of User ID
      user_id_ = find_game_json["User ID"].get<std::string>();
      game_type_ = static_cast<GameType>(find_game_json["Game Type"].get<int>());
      //packet_type_ = find_game_json["Packet Type"].get<PacketType>();
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }
}
