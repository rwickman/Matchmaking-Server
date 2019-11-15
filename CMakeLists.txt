cmake_minimum_required(VERSION 3.10)

# set the project name
project(Matchmaking-Server)

# Add Boost library
find_package(Boost 1.67.0 REQUIRED system thread regex)

# Add to search path
include_directories(${Boost_INCLUDE_DIR})

#Consider embedding in future
add_subdirectory(nlohmann)
add_subdirectory(server)

# add the executable
add_executable(Server server_asio.cpp)
add_executable(Client client_asio.cpp)

target_link_libraries(Server PUBLIC 
                      ${Boost_LIBRARIES}
		      MatchmakingServer
		      nlohmann_json)

target_link_libraries(Client PUBLIC 
                      ${Boost_LIBRARIES}
		      nlohmann_json)

