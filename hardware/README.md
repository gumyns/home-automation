## Prerequisites
Download gcc-arm: http://gnuarmeclipse.github.io/toolchain/install/

Generate toolchains, call this:
```commandline
python toolchainGenerator.py
```

Download CubeMX package for STM32F0, or whole STM32CubeMX
```
http://www.st.com/en/embedded-software/stm32cubef0.html
```

## Building
Setup proper toolchain for correct device:
```commandline
mkdir build 
cd build 
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/STM32F030x6.cmake
```
