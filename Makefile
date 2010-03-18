# TerraControl, mru 2009

DEV_SER = /dev/ttyS0
DEV_PAR = /dev/parport0


VERSION := $(shell sed -e 's/\#define VERSION "\(.*\)"/\1/p;d' firmware/version.h )

ARCH_FILES = firmware/main.c firmware/commandline.c firmware/ds1307.c	\
		firmware/eeprom.c firmware/hd4478.c firmware/i2c.c				\
		firmware/itoa.c firmware/main.c firmware/portmap.c				\
		firmware/selftest.c firmware/sht11.c firmware/time.c			\
		firmware/time_noRTC.c firmware/timeswitch.c firmware/tmp101.c	\
		firmware/uart.c firmware/commandline.h firmware/common.h		\
		firmware/ds1307.h firmware/eeprom.h firmware/hd4478.h			\
		firmware/i2c.h firmware/itoa.h firmware/portmap.h				\
		firmware/selftest.h firmware/sht11.h firmware/time.h			\
		firmware/timeswitch.h firmware/tmp101.h firmware/uart.h			\
		firmware/version.h Makefile firmware/TerraControl/Makefile		\
		firmware/Makefile pcb/Makefile pcb/TerraControl.sch				\
		pcb/TerraControl.pcb pcb/packages/rel_finder_40_31				\
		pcb/packages/relay-mru-1.sym

get_version:
	@echo $(VERSION)

build:
	@$(MAKE) -C firmware build

program: rights
	@$(MAKE) -C firmware program

gui:
	@$(MAKE) -C gui


sync:
	unison -silent -batch -auto -ui text terracontrol

remote_program:
	ssh ikarus 'cd ~/dev/erich/terrarium/; make sync && make clean program && make sync;'

rights:
	@if [ -e $(DEV_SER) -a ! -w $(DEV_SER) ]; then sudo chmod uog+rw $(DEV_SER); fi
	@if [ -e $(DEV_PAR) -a ! -w $(DEV_PAR) ]; then sudo chmod uog+rw $(DEV_PAR); fi

install_gcc:
	apt-get install gcc-avr uisp avr-libc binutils-avr gtkterm

clean: 
	@$(MAKE) -C firmware clean
	@$(MAKE) -C pcb clean

arch:
	@tar czf TerraControl-$(VERSION).tar.gz $(ARCH_FILES)


startgeda:
	$(MAKE) -C pcb startgeda

geda_update:
	$(MAKE) -C pcb update

.PHONY: clean rights build program arch geda sync install_gcc remote_program 

