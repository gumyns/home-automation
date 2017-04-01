#!/usr/bin/python
import sys
import os
import shutil
from subprocess import call

# store working dir
workingDir = os.getcwd()
# set current as working dir
os.chdir(os.path.dirname(os.path.abspath(__file__)))

copyPath = None

if len(sys.argv) == 2:
    copyPath = str(sys.argv[1])

if not os.path.exists("./build"):
    call(["mkdir", "build"])
os.chdir("./build")
call(["cmake", ".."])
call(["make"])
os.chdir("..")
if not copyPath is None:
    files = os.listdir("./build/lib")
    for file in files:
        shutil.move(os.path.join(os.path.dirname(os.path.abspath(__file__)), "build", "lib", file) , os.path.join(copyPath, file))
    # remove build files
    shutil.rmtree("./build", ignore_errors=True)
# restore working dir
os.chdir(workingDir)
