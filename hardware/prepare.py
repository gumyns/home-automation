#!/usr/bin/python
import os
import sys

libs = [
    os.path.expanduser("~") + '/opt/STM32/STM32Cube_FW_F0_V1.8.0'
]

devices = [
    ['STM32F030x6', libs[0]],
    ['STM32F042x6', libs[0]]
]

scripts = os.path.join(os.path.dirname(os.path.realpath(sys.argv[0])), "scripts")
currentDir = os.path.dirname(os.path.realpath(sys.argv[0]))

for device in devices:
    os.system("python " + os.path.join(scripts, "generateToolchain.py") + " " + currentDir + " " + device[0])

for device in devices:
    if not os.path.isdir(device[1]):
        print "Directory {0} doesn't exists. Skipping".format(device[1])
