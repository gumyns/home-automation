#!bin/sh

if [ ! -d "libs" ]; then
	mkdir libs
fi

cd libs

if [ ! -d "boost" ]; then
	wget https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2
	tar --bzip2 -xf ./boost_1_63_0.tar.bz2
	rm ./boost_1_63_0.tar.bz2
	cd boost_1_63_0
	./bootstrap.sh --with-libraries=thread,filesystem,system,log --prefix=../boost
	./b2 install
	rm -rf ./boost_1_63_0
	cd ..
fi

if [ ! -d "include" ]; then
	mkdir include
fi

if [ ! -s "include/json.hpp" ]; then 
	wget https://raw.githubusercontent.com/nlohmann/json/v2.0.10/src/json.hpp
	mv json.hpp include/

	echo https://github.com/zeromq/libzmq/releases/download/v4.2.0/zeromq-4.2.0.tar.gz
fi

echo Done!
