#!/usr/bin/python
import os
import sys
import subprocess

# STM32F030x6
template = \
"""    if ({device})
        set(STM32_STARTUP_FILE {path})
    endif ({device})
"""

directory = os.path.expanduser("~") + '/STM32Cube/Repository'
if not os.path.isdir(directory):
    sys.exit(directory + " does not exists, download STM32CubeMX and needed packages from there")

if len(sys.argv) == 3:
    targetDir = os.path.join(os.path.abspath(sys.argv[1]), "cmake", "Modules")
    list = sys.argv[2]
else:
    sys.exit("ERROR parameter missing -> python generateDirectories.py <directory> <comma separated devices list>")

with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "templates", "FindSTM32Startup.template"), 'r') as f:
    fileTemplate = f.read()

list = list.split(',')

output = ""
for device in list:
    findCMD = "find {directory} -name 'startup_{device}.s' | grep 'gcc'".format(directory=directory, device=device.lower())
    out = subprocess.Popen(findCMD, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    (stdout, stderr) = out.communicate()
    files = stdout.decode().split()
    if len(files) >= 1:
        file = files[0].strip()
        output = output + template.format(device=device, path=file)
    else:
        sys.exit("startup file {device} not found...".format(device=device.lower()))

with open(os.path.join(targetDir, "FindSTM32Startup.cmake"), 'w') as f:
    f.write(fileTemplate.format(placeholder=output))
    f.close()
