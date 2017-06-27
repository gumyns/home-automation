import os
import sys

directory = os.path.expanduser("~") + '/STM32Cube/Repository'
if not os.path.isdir(directory):
    sys.exit(directory + " does not exists, download STM32CubeMX and needed packages from there")

if len(sys.argv) == 3:
    targetDir = os.path.join(os.path.abspath(sys.argv[1]), "cmake")
    list = sys.argv[2]
else:
    sys.exit("ERROR parameter missing -> python generateDirectories.py <directory> <coma separated families list>")

with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "templates", "directory.template"), 'r') as f:
    template = f.read()

list = list.split(',')
packages = [f for f in os.listdir(directory) if os.path.isdir(os.path.join(directory, f))]

out = ""
for family in list:
    for package in packages:
        if family in package:
            print "Package for STM32{0} found, adding...".format(family)
            out = out + template.format(family_var="STM32_FAMILY", directory=os.path.join(directory, package), family= "STM32" + family)
        else:
            print "WARNING: Package for STM32{0} not found. Toolchain won't work correctly for this family." \
                  " Use STM32CubeMX and needed packages and download missing packages if needed.".format(family)

with open(os.path.join(targetDir, "ArmDirectories.cmake"), 'w') as f:
    f.write(out)
    f.close()
