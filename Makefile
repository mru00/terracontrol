# TerraControl, mru 2009

DEV_SER = /dev/ttyS0
DEV_PAR = /dev/parport0


build:
	@$(MAKE) -C src build

program: rights
	@$(MAKE) -C src program

rights:
	@if [ -e $(DEV_SER) -a ! -w $(DEV_SER) ]; then sudo chmod uog+rw $(DEV_SER); fi
	@if [ -e $(DEV_PAR) -a ! -w $(DEV_PAR) ]; then sudo chmod uog+rw $(DEV_PAR); fi

clean: 
	@$(MAKE) -C src clean
	@$(MAKE) -C pcb clean

arch:
	@tar czf TerraControl.tar.gz \
		src/main.c src/commandline.c src/ds1307.c src/eeprom.c src/hd4478.c src/i2c.c \
		src/itoa.c src/main.c src/misc.c src/portmap.c src/selftest.c src/sht11.c \
		src/time.c src/time_noRTC.c src/timeswitch.c src/tlv5620.c src/tmp101.c \
		src/uart.c \
		src/commandline.h src/common.h src/ds1307.h src/eeprom.h src/hd4478.h src/i2c.h \
		src/itoa.h src/misc.h src/portmap.h src/selftest.h src/sht11.h src/time.h \
		src/timeswitch.h src/tlv5620.h src/tmp101.h src/uart.h src/version.h \
		Makefile src/TerraControl/Makefile src/Makefile pcb/Makefile \
		pcb/TerraControl.sch pcb/TerraControl.pcb pcb/packages/rel_finder_40_31


geda:
	cd pcb && gschem TerraControl.sch &
	cd pcb && pcb TerraControl.pcb &


geda_update:
	$(MAKE) -C pcb update

.PHONY: clean rights build program arch geda