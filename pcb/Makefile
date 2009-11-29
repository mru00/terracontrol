
BASENAME=TerraControl


ELEMENTS = ./packages

VERBOSITY = 

update:
	gsch2pcb -f  -d $(ELEMENTS) $(BASENAME).sch $(VERBOSITY)

drc:
	gnetlist -g drc2 $(BASENAME).sch -o drc_output.txt

clean:
	-rm -vf $(BASENAME).net $(BASENAME).old.pcb $(BASENAME).cmd gnetlist.log gschem.log drc_output.txt $(BASENAME).new.pcb
	-rm -vf *~ *-
	-rm -vf *.backup

startgeda:
	-gschem $(BASENAME).sch &
	-pcb $(BASENAME).pcb &

.PHONY: update drc clean startgeda
