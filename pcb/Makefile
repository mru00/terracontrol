
BASENAME=TerraControl


ELEMENTS = ./packages

VERBOSITY = -v

update:
	gsch2pcb -f  -d $(ELEMENTS) $(BASENAME).sch $(VERBOSITY)

drc:
	gnetlist -g drc2 $(BASENAME).sch -o drc_output.txt

clean:
	-rm $(BASENAME).net $(BASENAME).old.pcb $(BASENAME).cmd gnetlist.log gschem.log drc_output.txt $(BASENAME).new.pcb

.PHONY: update drc clean