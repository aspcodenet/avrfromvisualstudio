CC=C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-gcc
LD=C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-ld
OBJCOPY="C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy"
OBJDUMP="C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objdump"
AVRSIZE="C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-size"

MCU=atmega328p

CFLAGS=-Wall -Wextra -Werror -Wstrict-prototypes -Wundef -pedantic \
		-Os -std=gnu99 -DF_CPU=16000000UL -mmcu=${MCU}
LDFLAGS=-mmcu=$(MCU)
PORT=\\\\.\\COM3

BIN=exefile

OUT=${BIN}.elf ${BIN}.hex ${BIN}.lss

SOURCES = \
		  main.c \
		  serial.c

OBJS = $(SOURCES:.c=.o)

all: $(OUT)
$(OBJS): Makefile

#-include $(OBJS:.o=,P)
%.o:%.c
	$(COMPILE.c) -MD -o $@ $<

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

flash: ${BIN}.hex
	C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude -F -V -c arduino -p ${MCU} -P ${PORT} -b 115200 -U flash:w:$<

isp: ${BIN}.hex
	avrdude -F -V -c avrisp2 -p ${MCU} -P ${PORT} -U flash:w:$<

clean:
	rm -f $(OUT) $(OBJS) *.map *.P *.d