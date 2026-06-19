#     _______  __   __  ______   ___   _______  _______  ______
#    |       ||  | |  ||      | |   | |       ||       ||    _ |
#    |    ___||  |_|  ||  _    ||   | |_     _||   _   ||   | ||
#    |   |___ |       || | |   ||   |   |   |  |  | |  ||   |_||_
#    |    ___||       || |_|   ||   |   |   |  |  |_|  ||    __  |
#    |   |___ |   _   ||       ||   |   |   |  |       ||   |  | |
#    |_______||__| |__||______| |___|   |___|  |_______||___|  |_|
#
#    the eh makefile

CC     ?= cc
CFLAGS ?= -march=native -mno-avx512f

# ============================================================================== #
#                          DO NOT EDIT PAST THIS POINT                           #
# ============================================================================== #

AR := ar rcs

override \
CFLAGS += -std=c99 -O2

# vendor pathing
VENDOR_LUA_PREFIX  := ../vendor/lua/
VENDOR_RGFW_PREFIX := ../vendor/rgfw/
ifeq ($(OS),Windows_NT)
VENDOR_LUA_PREFIX  := $(subst /,\,$(VENDOR_LUA_PREFIX))
VENDOR_RGFW_PREFIX := $(subst /,\,$(VENDOR_RGFW_PREFIX))
endif

override \
CFLAGS += -I$(VENDOR_LUA_PREFIX) -I$(VENDOR_RGFW_PREFIX)

# rgfw dependencies
ifeq ($(OS),Windows_NT)
	LDLIBS := -lopengl32 -lgdi32
else
	OS := $(shell uname -s)
	ifeq ($(OS),Darwin)
		LDLIBS := -framework Cocoa
	else
		LDLIBS := -lX11 -lGL -lm -lXrandr
	endif
endif

# targets and object defs
EH_E := eh
ifeq ($(OS),Windows_NT)
	EH_E := $(addsuffix .exe,$(EH_E))
endif

EH_T   := libeh.a
EH_O   := eh.o eh-rgfw.o

LUA_T  := liblua.a
LUA_O  := lapi.o     lcode.o   lctype.o   ldebug.o   ldo.o      ldump.o    lfunc.o   \
          lgc.o      llex.o    lmem.o     lobject.o  lopcodes.o lparser.o  lstate.o  \
		  lstring.o  ltable.o  ltm.o      lundump.o  lvm.o      lzio.o     ltests.o  \
                                                                                     \
          lbaselib.o ldblib.o  liolib.o   lmathlib.o loslib.o   ltablib.o  lstrlib.o \
	      lutf8lib.o loadlib.o lcorolib.o linit.o                                    \
                                                                                     \
	      lauxlib.o

RGFW_C := eh-rgfw.c
RGFW_H := RGFW.h

ONE_C  := eh-one.c

# fix vendored paths
LUA_T  := $(addprefix $(VENDOR_LUA_PREFIX),$(LUA_T))
LUA_O  := $(addprefix $(VENDOR_LUA_PREFIX),$(LUA_O))
RGFW_H := $(addprefix $(VENDOR_RGFW_PREFIX),$(RGFW_H))

ALL_T  := $(LUA_T) $(EH_T)
ALL_O  := $(LUA_O) $(EH_O)
ALL    := $(RGFW_C) $(ONE_C) $(ALL_O) $(ALL_T) $(EH_E)

# recipes
$(EH_T): $(EH_O)
	$(AR) $@ $^

$(LUA_T): $(LUA_O)
	$(AR) $@ $^

$(RGFW_C): $(RGFW_H)
ifeq ($(OS),Windows_NT)
	echo #define RGFW_IMPLEMENTATION > $(RGFW_C)
	echo #include "RGFW.h" >> $(RGFW_C)
	echo #undef RGFW_IMPLEMENTATION >> $(RGFW_C)
else
	echo "#define RGFW_IMPLEMENTATION" > $(RGFW_C)
	echo "#include \"RGFW.h\"" >> $(RGFW_C)
	echo "#undef RGFW_IMPLEMENTATION" >> $(RGFW_C)
endif

$(ONE_C): $(RGFW_C)
	$(file >$@,// eh unity file)
ifeq ($(OS),Windows_NT)
	$(foreach c,$(patsubst %.o,%.c,$(ALL_O)), \
		$(info echo #include "$(c)" >> $@)    \
		$(file >>$@,#include "$(c)")          \
	)
else
	$(foreach c,$(patsubst %.o,%.c,$(ALL_O)),  \
		$(info echo "#include \"$(c)\" >> $@") \
		$(file >>$@,#include "$(c)")           \
	)
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# phonies
.PHONY: run eh eh-release eh-devel script script-windows script-posix clean

run: eh-devel
	$(EH_E) | (cls || clear)
	@echo process finished with exit code:

eh: eh-release

eh-release: $(ONE_C)
	$(CC) $(CFLAGS) $< -o $(EH_E) $(LDLIBS)

eh-devel: $(ALL_T)
	$(CC) $(EH_T) $(LUA_T) -o $(EH_E) $(LDLIBS)

script: $(if $(filter Windows_NT,$(OS)),script-windows,script-posix)

script-windows:
	echo @rem This is the eh build script for Windows > build.bat
	echo. >> build.bat
	make eh -nB --no-print-directory >> build.bat OS=Windows_NT

script-posix:
	echo #!/bin/bash > build.sh
	echo >> build.sh
	make eh -nB --no-print-directory >> build.sh OS=

clean:
ifeq ($(OS),Windows_NT)
	del $(ALL) 2>nul
else
	rm $(ALL)
endif

.DEFAULT_GOAL := eh
