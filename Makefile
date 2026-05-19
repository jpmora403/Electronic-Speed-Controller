HEADERS=/home/jpmora403/avr8-gnu-toolchain-linux_x86_64/avr/include/avr
CC=avr-gcc
CLKSPD=20000000
CFLAGS=-mmcu=$(MCU) -Os -DF_CPU=$(CLKSPD)
MCU=avr16eb32
SRC=$(wildcard ./src/*.c) printf/printf.c
OBJ=$(patsubst ./src/%.c, ./obj/%.o, $(SRC))
OBJ_DIR=./obj
BIN_DIR=./bin
SRC_DIR=./src

all: $(BIN_DIR)/esc.hex

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I$(HEADERS) -I./include -I printf/ $(CFLAGS) -c $< -o $@

$(BIN_DIR)/esc.elf: $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/esc.hex: $(BIN_DIR)/esc.elf
	avr-objcopy -O ihex $< $@

temp: ./tmp/expanded.c

./tmp/expanded.c: ./src/esc.c
	$(CC) $(CFLAGS) -E -I./include -I$(HEADERS) -o $@ $<

.PHONY: flash all clean

flash: $(BIN_DIR)/esc.hex
	avrdude -c serialupdi -P /dev/ttyACM0 -b 115200 -p avr16eb32 -U flash:w:$(BIN_DIR)/esc.hex:i

clean:
	rm -f bin/* obj/* tmp/*
