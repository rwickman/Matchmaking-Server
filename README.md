# Matchmaking-Server
## Dependencies
Since the version of boost that is installed by package manager differs between distros, it is easier to just install manually.
Install boost from source:
```shell
wget https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.bz2
tar --bzip2 -xf boost_1_71_0.tar.bz2
cd boost_1_71_0
./bootstrap.sh --prefix=/usr && ./b2 stage -j 2 threading=multi link=shared
sudo ./b2 install threading=multi link=shared && ln -svf detail/sha1.hpp /usr/include/boost/uuid/sha1.hpp
```

## TODO
* Fix error for writting json to data as it sometimes doesnt work right
* If server crashes reboot it
* Need to verify TCP connection is still active before calling host or join callbacks
* Look into when boost post should be used for optimization purposes
* Consider using custom deleter for User pointer to log users
* Allow users to join game in session if possible
