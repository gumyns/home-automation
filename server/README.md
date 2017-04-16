## Prerequisites
Make sure you have dev tools

Fedora:
> dnf group install 'Development Tools'	
>
> dnf install cmake gcc gcc-c++ python27 libtool sqlite-devel

There are also few dependencies, that have to be built from sources (at least on arm based devices). There are python scrips that can do that for you. Call:

> python scripts/resolveDependencies.py libs

## Run info ##

Make sure your user can use /dev/tty devices:

> sudo usermod -a -G dialout <username>
> sudo chmod 666 /dev/ttyUSB0

## Project info ##

For eclipse:

- install CMake Build Support plugin

For CLion

- just import project and you're fine

## Errors ##
If you encounter such error:
```bash
locale::facet::_S_create_c_locale name not valid
```
That means you have wrong locale on system, and you need to setup it correctly. 
```bash 
export LC_ALL=C
```

## Not working usb to ttl
```bash
apt-get install libmtp-runtime
```

## Server 
1. Install openssl-devel bzip2-devel expat-devel lmdb-devel libdb-cxx-devel
2. Run dependencies.sh to prepare all dependencies for server
