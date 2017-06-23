#!/usr/bin/python
import os
import sys
import subprocess

devices = ['STM32F030x6']

template = """set(ENV{{PATH}} {gcc_dir})
set(GCC_ARM_DIRECTORY {gcc_dir})

add_definitions(-D{device})

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_RANLIB arm-none-eabi-ranlib)
set(CMAKE_LINKER arm-none-eabi-ld)

set(COMMON_FLAGS " -Wall -Wextra -nostartfiles -mcpu=cortex-m0 -mthumb -mthumb-interwork -mfloat-abi=soft -ffunction-sections -fdata-sections -g -fno-common -fmessage-length=0  --specs=nano.specs -Os -fsigned-char -ffreestanding -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize -fno-builtin")
set(CMAKE_CXX_FLAGS_INIT "${{COMMON_FLAGS}} -std=c++14")
set(CMAKE_C_FLAGS_INIT "${{COMMON_FLAGS}} -std=gnu99")
set(CMAKE_ASM_FLAGS_INIT -nostdinc)
set(CMAKE_EXE_LINKER_FLAGS_INIT -Wl,-gc-sections,-M=binary.map,-Map,"${{PROJECT_NAME}}.map",-o"${{PROJECT_NAME}}.elf")

set(CMAKE_C_FLAGS "${{COMMON_FLAGS}} -std=gnu99" CACHE INTERNAL "c compiler flags")
set(CMAKE_CXX_FLAGS "${{COMMON_FLAGS}} -std=c++14" CACHE INTERNAL "cxx compiler flags")
set(CMAKE_ASM_FLAGS "${{COMMON_FLAGS}} -x assembler-with-cpp " CACHE INTERNAL "asm compiler flags")
"""

findCMD = 'find ~/opt -name "arm-none-eabi-gcc" | head -1 | rev | cut -c 18- | rev'
out = subprocess.Popen(findCMD,shell=True,stdin=subprocess.PIPE, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
(stdout, stderr) = out.communicate()
files = stdout.decode().split()
if len(files) is 1:
    directory = files[0].strip()
else:
    sys.exit("GCC for arm not found...")


srcDir = os.path.join(os.path.dirname(os.path.abspath(str(sys.argv[0]))), "toolchains")
if not os.path.isdir(srcDir):
    subprocess.call(["mkdir", srcDir])

for dev in devices:
    with open(os.path.join(srcDir, "{0}.cmake".format(dev)), 'w') as f:
        f.write(template.format(gcc_dir=directory, device=dev))
        f.close()
