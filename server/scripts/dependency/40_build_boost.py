#!/usr/bin/python
import sys
import os
from subprocess import call

dependencyName = "build_boost"
dependencyVersion = "1.63.0"

if len(sys.argv) == 2:
    directory = os.path.abspath(str(sys.argv[1]))
else:
    sys.exit("ERROR directory missing")

srcDir = os.path.join(directory, "boost_1_63_0")

print "Boostraping {0}-{1}...".format(dependencyName, dependencyVersion)
call(["./bootstrap.sh", '--with-libraries=thread,filesystem,system --prefix=../boost'], cwd = srcDir)
call(["./b2", 'threading=multi'], cwd = srcDir)
