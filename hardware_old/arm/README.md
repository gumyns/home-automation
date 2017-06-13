## Prerequisites
Download gcc-arm: http://gnuarmeclipse.github.io/toolchain/install/

Generate toolchains, call this:
```commandline
python toolchainGenerator.py
```

## Building
Setup proper toolchain for correct device:
```commandline
mkdir build 
cd build 
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/STM32F030x6.cmake
```