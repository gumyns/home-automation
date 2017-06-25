#!/usr/bin/python
import os
import sys
import subprocess

devices = ['STM32F030x6']

scripts = os.path.join(os.path.dirname(os.path.realpath(sys.argv[0])), "scripts")
currentDir = os.path.dirname(os.path.realpath(sys.argv[0]))

for device in devices:
    os.system("python " + os.path.join(scripts, "generateToolchain.py") + " " + currentDir + " " + device)
