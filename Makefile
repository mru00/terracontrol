# TerraControl, mru 2009

DEV_SER = /dev/ttyS0
DEV_PAR = /dev/parport0


VERSION := $(shell sed -e 's/\#define VERSION "\(.*\)"/\1/p;d' src/version.h )

ARCH_FILES = \
		src/main.c src/commandline.c src/ds1307.c src/eeprom.c src/hd4478.c src/i2c.c \
		src/itoa.c src/main.c src/portmap.c src/selftest.c src/sht11.c \
		src/time.c src/time_noRTC.c src/timeswitch.c src/tmp101.c \
		src/uart.c \
		src/commandline.h src/common.h src/ds1307.h src/eeprom.h src/hd4478.h src/i2c.h \
		src/itoa.h src/portmap.h src/selftest.h src/sht11.h src/time.h \
		src/timeswitch.h src/tmp101.h src/uart.h src/version.h \
		Makefile src/TerraControl/Makefile src/Makefile pcb/Makefile \
		pcb/TerraControl.sch pcb/TerraControl.pcb pcb/packages/rel_finder_40_31 pcb/packages/relay-mru-1.sym

get_version:
	@echo $(VERSION)

build:
	@$(MAKE) -C src build

program: rights
	@$(MAKE) -C src program

sync:
	unison -silent -batch -auto -ui text terracontrol

remote_program:
	ssh ikarus 'cd ~/dev/erich/terrarium/; make sync && make program && make sync;'

rights:
	@if [ -e $(DEV_SER) -a ! -w $(DEV_SER) ]; then sudo chmod uog+rw $(DEV_SER); fi
	@if [ -e $(DEV_PAR) -a ! -w $(DEV_PAR) ]; then sudo chmod uog+rw $(DEV_PAR); fi

install_gcc:
	apt-get install gcc-avr uisp avr-libc binutils-avr gtkterm

clean: 
	@$(MAKE) -C src clean
	@$(MAKE) -C pcb clean

arch:
	@tar czf TerraControl-$(VERSION).tar.gz $(ARCH_FILES)


startgeda:
	$(MAKE) -C pcb startgeda

geda_update:
	$(MAKE) -C pcb update

.PHONY: clean rights build program arch geda sync install_gcc remote_program 

