## Flashing ##

On Windows

	ST provide an application called the 'ST Flash Loader Demonstrator' that allows you to easily flash your device. Just download the tool and follow their instructions.

On Mac OS / Linux 

    Open a Terminal Window

	Download flashing tool git clone http://git.code.sf.net/p/stm32flash/code stm32flash-code

	Compile it:
		cd stm32flash-code 
		sudo make install

    Make sure you have Python installed (type python --version and see if anything happens)

    Download the stm32loader.py Python script from https://github.com/espruino/Espruino/blob/master/scripts/stm32loader.py or use bundled

    Run python stm32loader.py -p MySerialPort -evw your_compiled_binary.bin

        On Mac OS, MySerialPort will probably look a lot like /dev/tty.usbserial### where ### is a number. You can use the 'Tab' key to autocomplete once you have typed /dev/tty.usbserial
        On Linux, MySerialPort will probably look a lot like /dev/ttyUSB# where # is a number. If you only have one USB-Serial device plugged in, it's almost certainly /dev/ttyUSB0

    Note: The flasher may give you an error message such as Chip replied with a NACK. If so, just try running it again without resetting your board.


The instructions are detailed more fully here: http://leaflabs.com/docs/bootloader.html#flashing-a-custom-bootloader

## After Flashing ##

Just ensure that the BOOT0 pin is set to 0 again.
