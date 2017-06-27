#!/usr/bin/python
import os
import sys
from subprocess import call

# toolchain defines
libs = [
    ["F0", os.path.expanduser("~") + '/opt/STM32/STM32Cube_FW_F0_V1.8.0'] # ~/opt/...
]

families = ["F0", "F1"]

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
print "stm32flash located at: " + stm32flashBinary

# toolchain generator
for device in devices:
    os.system("python " + os.path.join(scriptsDir, "generateToolchain.py") + " " + currentDir + " " + device)

# cmake generator
familyList = ""
for family in families:
    familyList = familyList + "," + family
os.system("python " + os.path.join(scriptsDir, "generateDirectories.py") + " " + currentDir + " " + familyList[1:])
# find CMSIS
with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "scripts", "templates", "FindCMSIS.template"), 'r') as f:
    template = f.read()
    call(["mkdir", "-p", os.path.join(currentDir, "cmake", "Modules")])
    with open(os.path.join(currentDir, "cmake", "Modules", "FindCMSIS.cmake"), 'w') as f:
        f.write(template)
        f.close()
# find HAL
with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "scripts", "templates", "FindHAL.template"), 'r') as f:
    template = f.read()
    call(["mkdir", "-p", os.path.join(currentDir, "cmake", "Modules")])
    with open(os.path.join(currentDir, "cmake", "Modules", "FindHAL.cmake"), 'w') as f:
        f.write(template)
        f.close()