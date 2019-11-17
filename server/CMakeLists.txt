add_library(MatchmakingServer matchmaking_server.cpp)
add_library(TCPConnection tcp_connection.cpp)
add_library(Packet packet.cpp)
add_library(JoinPacket join_packet.cpp)

target_link_libraries(TCPConnection PUBLIC JoinPacket)
target_link_libraries(MatchmakingServer PUBLIC TCPConnection)
