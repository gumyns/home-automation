#!/usr/bin/python
import sys
import os
import shutil
from subprocess import call

if len(sys.argv) == 2:
	target = os.path.abspath(str(sys.argv[1]))
else:
	sys.exit("ERROR directory missing");

if not os.path.exists(target):
    call(["mkdir", target])
if not os.path.exists(os.path.join(target, "plugin")):
    call(["mkdir", os.path.join(target, "plugin")])
if not os.path.exists(os.path.join(target, "plugin", "device")):
    call(["mkdir", os.path.join(target, "plugin", "device")])
if not os.path.exists(os.path.join(target, "plugin", "hub")):
    call(["mkdir", os.path.join(target, "plugin", "hub")])

path = os.path.join(target, "plugin", "device")
os.path.abspath("./build/plugin/device")
for root, subFolders, files in os.walk(os.path.abspath("../plugins/device")):
    if 'build.py' in files:
		os.system("python " + os.path.join(root, 'build.py') + " " + path)

path = os.path.join(target, "plugin", "hub")
for root, subFolders, files in os.walk(os.path.abspath("../plugins/hub")):
    if 'build.py' in files:
		os.system("python " + os.path.join(root, 'build.py') + " " + path)
