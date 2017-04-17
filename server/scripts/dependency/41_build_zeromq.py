#!/usr/bin/python
import dep_lib
import sys
import time
import os
from subprocess import call
from subprocess import Popen

dependencyName = 'build_zeromq'
dependencyVersion = "4.2.0"

if len(sys.argv) == 2:
    directory = os.path.abspath(str(sys.argv[1]))
else:
    sys.exit("ERROR directory missing")

srcDir = os.path.join(directory, "zeromq")

print "Boostraping {0}-{1}...".format(dependencyName, dependencyVersion)
call(["./autogen.sh", ''], cwd = srcDir)
call(["./configure", ''], cwd = srcDir)
time.sleep(.5)
print srcDir
make_process = Popen("make", cwd = srcDir)
make_process.wait()
