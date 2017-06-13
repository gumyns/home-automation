#!/usr/bin/python
import os

def cls():
    os.system('cls' if os.name=='nt' else 'clear')


def hubType():
    print "Hub project name:"
    name = raw_input()

    return

def deviceType():
    print "Device project name:"
    name = raw_input()

    return


typeChoice = ["Device", "Hub"]

cls()
print "Choose project type:"
for i, project in enumerate(typeChoice):
    print str(i + 1) + ". " + project

choice = 0
while True:
    try:
        choice = int(raw_input())
    except IOError:
        print "Try again"
        continue
    if choice > 0 and choice < 3:
        break
    else:
        print "Try again"
        continue

cls()
if choice == 1:
    deviceType()
else:
    hubType()


