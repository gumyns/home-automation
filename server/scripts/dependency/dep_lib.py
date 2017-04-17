#!/usr/bin/python
import json
import os
import sys
import urllib2
from subprocess import call


def unzipTar(src, dst): 
	import tarfile
	tar = tarfile.open(src)
	tar.extractall(dst)
	tar.close()

def unzipZip(src, dst): 
	import zipfile
	zip_ref = zipfile.ZipFile(src, 'r')
	zip_ref.extractall(dst)
	zip_ref.close()

def download(what, into):
	req = urllib2.Request(what)
	response = urllib2.urlopen(req)
	CHUNK = 16 * 1024
	with open(into, 'wb') as f:
        while True:
			chunk = response.read(CHUNK)
			if not chunk:
                break
            f.write(chunk)

def filesExist(*files):
	exists = True
	for f in files:
		exists &= os.path.exists(f)
	return exists

def createDir(name):
	if not os.path.exists(name):
		print "Creating directory: " + name
        call(["mkdir", name])

def getVersion(name):
	fname = os.path.join(os.path.dirname(os.path.realpath(sys.argv[0])), "versions.json")
	if not os.path.isfile(fname):
		with open(fname, 'a') as f:
			f.write("{}")			
			f.close()
	with open(fname) as f:
		versions = json.load(f)
		if name in versions:
			return versions[name]
    return None;

def setVersion(name, version):
	fname = os.path.join(os.path.dirname(os.path.realpath(sys.argv[0])), "versions.json")
	if not os.path.isfile(fname):
		with open(fname, 'a') as f:
			f.write("{}")			
			f.close()
	with open(fname, 'r') as f:
		versions = json.load(f)
		versions[name] = version
		f.close()
		with open(fname, 'w') as ff:
			json.dump(versions,ff)
    return;
