First create libs directory:

```bash
mkdir libs
cd libs
```

## Downloads
```bash
wget https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2
tar --bzip2 -xf ./boost_1_63_0.tar.bz2
rm ./boost_1_63_0.tar.bz2
```

# For x86
## Boost
```bash
cd boost_1_63_0
./bootstrap.sh --prefix=../boost
./b2 install
rm -rf ./boost_1_63_0
cd ..
```

# For arm
```bash
cd boost_1_63_0
./bootstrap.sh --prefix=../boost
```
Now edit 
