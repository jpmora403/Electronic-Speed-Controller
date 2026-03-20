HEADERS=/home/jpmora403/avr8-gnu-toolchain-linux_x86_64/avr/include/avr
CC=avr-gcc
CLKSPD=20000000
CFLAGS=-mmcu=$(MCU) -Os -DF_CPU=$(CLKSPD)
MCU=avr16eb32
SRC=$(wildcard ./src/*.c)
OBJ=$(patsubst ./src/%.c, ./obj/%.o, $(SRC))
OBJ_DIR=./obj
BIN_DIR=./bin
SRC_DIR=./src

all: $(BIN_DIR)/main.hex

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I$(HEADERS) -I./include $(CFLAGS) -c $< -o $@

$(BIN_DIR)/main.elf: $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/main.hex: $(BIN_DIR)/main.elf
	avr-objcopy -O ihex $< $@


.PHONY: flash

flash: $(BIN_DIR)/main.hex
	avrdude -c jtag2updi -P /dev/ttyACM0 -b 115200 -p avr16eb32 -U flash:w:main.hex:i 
