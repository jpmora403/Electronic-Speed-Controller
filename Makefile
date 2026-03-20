HEADERS="/home/jpmora403/avr8-gnu-toolchain-linux_x86_64/avr/include/avr"

main: main.c init.c
	avr-gcc -mmcu=avr16eb32 -I$(HEADERS) -Os -DF_CPU=1000000UL -o main.o main.c init.c

PHONY: flash

flash: main.o
	avr-objcopy -O ihex blink.o blink.hex
	avrdude -c jtag2updi -P /dev/ttyACM0 -b 115200 -p avr16eb32 -U flash:w:main.hex:i 
