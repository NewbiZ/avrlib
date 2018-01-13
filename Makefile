CC=avr-gcc
CFLAGS=-Os -mcall-prologues -Wall -std=c99 -mmcu=atmega328 -Iinclude
OBJ2HEX=avr-objcopy
AVRD=avrdude
TARGET=serial
PROGRAMMER=stk600
PROGRAMMER_IFACE=usb
MCU=m328
OBJS=\
	src/ringbuffer.o\
	src/uart.o\
	src/main.o

all: program.hex
	@$(AVRD) -p $(MCU) -c $(PROGRAMMER) -P $(PROGRAMMER_IFACE) -U flash:w:program.hex

program.hex: $(OBJS)
	$(CC) $(CFLAGS) -o program.obj $^
	$(OBJ2HEX) -R .eeprom -O ihex program.obj $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

parms:
	echo "parms" | avrdude -t -p m2560 -P usb -c stk600

rs232:
	sudo modprobe usbserial vendor=0x067b product=0x2303
	sudo chmod 0666 /dev/ttyUSB0

clean:
	rm -f program.{hex,obj} $(OBJS)
