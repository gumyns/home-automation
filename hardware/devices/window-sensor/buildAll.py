#!/usr/bin/python
import os
import timeit
import subprocess
from multiprocessing.dummy import Pool as ThreadPool

addressPool = 64
device = "STM32F030x6"
projectName = "{0}/arm.device.window-sensor{1}.hex"

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

start = timeit.default_timer()

subprocess.call(["mkdir", "-p", "bin"])

pool = ThreadPool(16)
pool.map(build, range(0,addressPool))
pool.close()
pool.join()

print timeit.default_timer() - start