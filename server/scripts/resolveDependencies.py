#!/usr/bin/python
import sys
import os
from subprocess import call

if len(sys.argv) == 2:
	directory = os.path.abspath(str(sys.argv[1]))
else:
	sys.exit("ERROR directory missing");

if not os.path.exists(directory):
	print "Creating directory: " + directory
	call(["mkdir", directory])

scripts = os.path.join(os.path.dirname(os.path.realpath(sys.argv[0])), "dependency")

files = [f for f in os.listdir(scripts) if os.path.isfile(os.path.join(scripts, f)) and os.path.join(scripts, f).endswith(".py")]
files.sort()
for f in files:
	os.system("python " + os.path.join(scripts, f) + " " + directory)


