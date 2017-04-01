## Project info ##


## Build info ##
CMake:

```bash
mkdir build
cd build
cmake ..
make
```

For eclipse:

Well, you need to configure project for Eclipse like:

 > mkdir eclipse
 > cd eclipse
 > cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
or 
 > cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..

For CLion:

- just import project and you're fine
