
#F_OSC = 11059201L
F_OSC = 12288000L
MCU = atmega8
MCU_DUDE = m8

# List C source files here. (C dependencies are automatically generated.)
SRC = main.c  uart.c time.c timeswitch.c portmap.c \
	i2c.c ds1307.c eeprom.c hd4478.c commandline.c selftest.c \
	sht11.c itoa.c pcf8574a.c

RELEASE_DIR = ../releases
BUILD_ID_FILE = build-id.h
VERSION_FILE = version.h


GET_DEFINES = $(CC) $(ALL_CFLAGS) -mmcu=$(MCU) -E -dM $(SRC) -Werror
BUILD := $(shell sed -e 's/\#define BUILD_ID "\(.*\)"/\1/p;d' $(BUILD_ID_FILE))
VERSION := $(shell sed -e 's/\#define VERSION "\(.*\)"/\1/p;d' $(VERSION_FILE))
GET_BRANCH = $(shell git branch | sed -e 's/* \(.*\)/\1/p;d')

br:
	echo $(GET_BRANCH)

DATE = $(shell date +%Y%m%d)
HOST = $(shell uname -n)
RELEASE_FILENAME = $(TARGET)-$(HOST)-$(DATE)-$(VERSION)-b$(BUILD)

get_defines: $(SRC)
	$(call GET_DEFINES)

erase_flash:
	$(UISP) $(UISP_FLAGS) --erase

increase_build_number:
	@touch $(BUILD_ID_FILE)
	@echo "#define BUILD_ID \"$$(( $(BUILD) + 1 ))\"" > $(BUILD_ID_FILE)

find_dummy:
	@$(call GET_DEFINES) > /dev/null

check_branch:
	@[ $(GET_BRANCH) = "master" ] || ( echo "error: not on branch 'master'!"; false)

release: find_dummy increase_build_number build sizeafter
	@git commit -a -m "committing everything for TAG $(RELEASE_FILENAME)"
	@git tag -m "TAG for $(RELEASE_FILENAME)" $(RELEASE_FILENAME) master
	@echo
	@echo "Released as $(RELEASE_FILENAME)"
	@echo

FUSE_L = 0xef
FUSE_H = 0xc9


#CFLAGS += -Werror

-include Makefile.atmel


.PHONY: profile_size erase_flash release get_defines