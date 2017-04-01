## Before you start ## 
```bash
apt-get install gcc g++ libtool pkg-config build-essential autoconf automake libicu-dev
```
## Cmake ##
Make sure that your system already have CMake at least 3.6.2, If not, update or download from sources, compile and install it.
```bash
wget https://cmake.org/files/v3.7/cmake-3.7.2.tar.gz
tar -xzvf cmake-3.7.2.tar.gz
rm cmake-3.7.2.tar.gz
cd cmake-3.7.2
./bootstrap
make
make install
```
## Boost ##
```bash
wget https://downloads.sourceforge.net/project/boost/boost/1.63.0/boost_1_63_0.tar.gz?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F1.63.0%2F&ts=1486139651&use_mirror=vorboss
```
## ZeroMQ ## 
```bash
git clone https://github.com/zeromq/libzmq.git
./autogen.sh
/configure
make
```

## Server
```bash
git clone https://gumyns@bitbucket.org/gumyns/smarthomeserver.git
```
