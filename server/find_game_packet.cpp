#include "find_game_packet.hpp"

namespace Matchmaking
{
  FindGamePacket::FindGamePacket()
  {
  }

  std::string FindGamePacket::get_user_id()
  {
    return user_id;
  }

  GameType FindGamePacket::get_game_type()
  {
    return game_type;
  }

  bool FindGamePacket::decode_find_game()
  {
    try
    {
      nlohmann::json find_game_json = nlohmann::json::parse(body());
      // In the future consider doing some authentication of User ID
      user_id = find_game_json["User ID"].get<std::string>();
      game_type = static_cast<GameType>(find_game_json["Game Type"].get<int>());
      return true;
    }
    catch(std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  }
}
