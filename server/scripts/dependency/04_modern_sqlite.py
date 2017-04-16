#!/usr/bin/python
import dep_lib
import sys
import os
import shutil

dependencyName = "modern_sqlite"
dependencyVersion = "3.1"

if len(sys.argv) == 2:
    directory = os.path.abspath(str(sys.argv[1]))
else:
    sys.exit("ERROR directory missing");

dstDir = os.path.join(directory, "include")
dstFile = os.path.join(dstDir, "modern_sqlite.zip")

neededFiles = not dep_lib.filesExist(os.path.join(dstDir, dependencyName, 'hdr', "sqlite_modern_cpp.h"))

dep_lib.createDir(dstDir)

if not dependencyVersion == dep_lib.getVersion(dependencyName) or neededFiles:
    print "Downloading {0}-{1}...".format(dependencyName, dependencyVersion)
    dep_lib.download("https://github.com/aminroosta/sqlite_modern_cpp/archive/v3.1.zip", dstFile)
    print "Uzipping {0}-{1}...".format(dependencyName, dependencyVersion)
    dep_lib.unzipZip(dstFile, dstDir)
    # move needed files
    os.rename(os.path.join(dstDir, 'sqlite_modern_cpp-3.1'), os.path.join(dstDir, dependencyName))
    print "Removing unnecessary files..."
    os.remove(dstFile) # remove zip
    dep_lib.setVersion(dependencyName, dependencyVersion)


