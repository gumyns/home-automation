#!/usr/bin/python
import os
import sys
from subprocess import call

# toolchain defines
libs = [
    os.path.expanduser("~") + '/opt/STM32/STM32Cube_FW_F0_V1.8.0' # ~/opt/...
]

devices = [
    'STM32F030x6',
    'STM32F042x6'
]
# utils
currentDir = os.path.dirname(os.path.realpath(sys.argv[0]))
scriptsDir = os.path.join(os.path.dirname(os.path.realpath(sys.argv[0])), "scripts")

# stm32flash download and compile
stm32flashDir = os.path.join(os.path.dirname(os.path.realpath(sys.argv[0])), "stm32flash")
stm32flashBinary = os.path.join(stm32flashDir, "stm32flash")

if not os.path.isdir(stm32flashDir):
    os.system("git clone http://git.code.sf.net/p/stm32flash/code stm32flash")
if not os.path.exists(stm32flashBinary):
    call("make", cwd = stm32flashDir)

# toolchain generator
for device in devices:
    os.system("python " + os.path.join(scriptsDir, "generateToolchain.py") + " " + currentDir + " " + device)

# cmake generator
for lib in libs:
    if not os.path.isdir(lib):
        print "Directory {0} doesn't exists. Skipping".format(lib)
