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

