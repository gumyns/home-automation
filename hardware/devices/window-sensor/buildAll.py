#!/usr/bin/python
import os
import timeit
import subprocess
import re
from multiprocessing.dummy import Pool as ThreadPool

# address range from 0 to specified one will be generated
addressPool = 64
# device aka toolchain name
device = "STM32F030x6"
# definition of thread worker
def build(addr):
    subprocess.call(["mkdir", "-p", "build{0}".format(addr)])
    subprocess.call(["cmake",
                     "-DCMAKE_TOOLCHAIN_FILE=~/projects/home-automation/hardware/cmake/toolchains/{0}.cmake".format(device),
                     "-DI2C_ADDRESS={0}".format(addr),
                     ".."
                     ], cwd="build{0}".format(addr), stdout=open(os.devnull, 'wb'))
    subprocess.call(["make","-k"], cwd="build{0}".format(addr), stdout=open(os.devnull, 'wb'))
    subprocess.call(["cp", projectName.format("build{0}".format(addr), ""), projectName.format("bin", "_" + str(addr))])
    subprocess.call(["rm", "build{0}".format(addr), "-r"])
# just time measurement
start = timeit.default_timer()
# open project file and read project name!
with open(os.path.join(os.path.dirname(os.path.realpath(__file__)), "CMakeLists.txt"), 'r') as f:
    name = re.search("project\(([a-zA-z-_.]*) C CXX ASM\)", f.read()).group(1)
projectName = "{{0}}/{1}{{1}}.hex".format('{0}', name)
# create bin dir
subprocess.call(["mkdir", "-p", "bin"])
# setup threads for each address start build
pool = ThreadPool(16)
pool.map(build, range(0,addressPool))
pool.close()
pool.join() # wait
# just write how much did it take
print timeit.default_timer() - start