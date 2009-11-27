

DEV_SER = /dev/ttyS0
DEV_PAR = /dev/parport0




rights:
	@if [ -e $(DEV_SER) -a ! -w $(DEV_SER) ]; then sudo chmod uog+rw $(DEV_SER); fi
	@if [ -e $(DEV_PAR) -a ! -w $(DEV_PAR) ]; then sudo chmod uog+rw $(DEV_PAR); fi



clean: 
	make -C src clean
	make -C pcb clean



.PHONY: clean rights