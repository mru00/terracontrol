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

.PHONY: clean rights