#!/usr/bin/python
import os
import sys
from subprocess import Popen
from subprocess import call

srcDir = os.path.join(os.path.dirname(os.path.abspath(str(sys.argv[0]))), "build")
call(["mkdir", srcDir])
call(["cmake", '..'], cwd=srcDir)
make_process = Popen("make", cwd=srcDir)
make_process.wait()
