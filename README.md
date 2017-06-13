# Licenses
Code: [Apache 2.0](./LICENSE) ([tl;dr](https://choosealicense.com/licenses/apache-2.0/))

PCB: [CC-BY](./CC-BY.md) ([tl;dr](https://creativecommons.org/licenses/by/4.0/))

# What is it?
STM32 ARM based home automation system. Devices are built with STM32 F0 series microcontrollers (mostly with [STM32F030F4](http://www.st.com/en/microcontrollers/stm32f0x0-value-line.html?querycriteria=productId=LN1826), cheapest one). Project provides also a plugin for [OpenHab2](http://docs.openhab.org/) ([demo](http://demo.openhab.org:8080/start/index)), that allows integration also with other automation systems.

## Architecture
Generally it looks like this:

computer <=> gateway <=> hub <=> device 

On top there's a computer with OpenHab2 running with plugin configured (e.g. PC, RaspberryPi, Odroid, whatever that can run Java8).

Gateway is some cheap ARM based board with Linux, like Rasperry Zero, NanoPi, and communicates with central computer utilizing distributed system built on top of TCP/IP.

Hub is an ARM based board, that can communicate with gateway using any of supported protocols, and can communicate with devices. Amount of ports is configurable.

Device is just a worker (also ARM based board), that communitates with hubs using specific protocol, and provides data to the system.

#### This repository contains following modules
##### - [OpenHab2 plugin](./openhab2)
##### - [C++ server and plugins for gateways](./server)
##### - [PCB layouts and microcontrollers code](./hardware)

# NOTE
This project is in early stage, it's already a working prototype but far from final product.
