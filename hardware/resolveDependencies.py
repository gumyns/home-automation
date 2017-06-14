#!/usr/bin/python
import os
import sys
from subprocess import call

directory = os.path.dirname(os.path.abspath(str(sys.argv[0])))
if not os.path.exists(os.path.join(directory, "stm32-cmake")):
    call(["git", "clone", "https://github.com/ObKo/stm32-cmake.git"])
