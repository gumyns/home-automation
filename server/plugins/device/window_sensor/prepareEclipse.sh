#!/bin/sh
mkdir eclipse
cd eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
