#include "join_packet.hpp"

namespace Matchmaking
{
  JoinPacket::JoinPacket()
  {
  }

  std::string JoinPacket::get_user_id()
  {
    return user_id;
  }

  GameType JoinPacket::get_game_type()
  {
    return game_type;
  }

  bool JoinPacket::decode_join()
  {
    try
    {
      nlohmann::json join_json = nlohmann::json::parse(body());
      // In the future consider doing some authentication of User ID
      user_id = join_json["User ID"].get<std::string>();
      game_type = static_cast<GameType>(join_json["Game Type"].get<int>());
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }
}
