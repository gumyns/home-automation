#!/usr/bin/python
import os
import sys
import re
import subprocess

if len(sys.argv) == 3:
    targetDir = os.path.join(os.path.abspath(sys.argv[1]), "cmake", "toolchains")
    device = sys.argv[2]
else:
    sys.exit("ERROR parameter missing -> python generateToolchain.py <directory> <device name>");

with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "templates", "toolchain.template"), 'r') as f:
    template = f.read()

findCMD = 'find ~/opt -name "arm-none-eabi-gcc" | head -1 | rev | cut -c 18- | rev'
out = subprocess.Popen(findCMD, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
(stdout, stderr) = out.communicate()
files = stdout.decode().split()
if len(files) is 1:
    directory = files[0].strip()
else:
    sys.exit("GCC for arm not found...")

if not os.path.isdir(targetDir):
    subprocess.call(["mkdir", "-p", targetDir])

family = re.match("STM32[FL][0-9]", device).group()

with open(os.path.join(targetDir, "{0}.cmake".format(device)), 'w') as f:
    f.write(template.format(gcc_dir=directory, device=device, family=family))
    f.close()
