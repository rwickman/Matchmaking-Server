cmake_minimum_required(VERSION 3.10)

# set the project name
project(Matchmaking-Server)

# Add Boost library
find_package(Boost REQUIRED system thread regex)

# Add to search path
include_directories(${Boost_INCLUDE_DIR})

# add the executable
add_executable(Matchmaking-Server server_asio.cpp)
add_executable(Matchmaking-Client client_asio.cpp)

target_link_libraries(Matchmaking-Server PUBLIC ${Boost_LIBRARIES})
target_link_libraries(Matchmaking-Client PUBLIC ${Boost_LIBRARIES})

