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
ifeq ($(OS),Windows_NT)
VENDOR_LUA_PREFIX  := $(subst /,\,$(VENDOR_LUA_PREFIX))
endif

override \
CFLAGS += -I$(VENDOR_LUA_PREFIX)

# targets and object defs
EH_E := eh
ifeq ($(OS),Windows_NT)
	EH_E := $(addsuffix .exe,$(EH_E))
endif

EH_T   := libeh.a
EH_O   := eh.o

LUA_T  := liblua.a
LUA_O  := lapi.o     lcode.o   lctype.o   ldebug.o   ldo.o      ldump.o    lfunc.o   \
          lgc.o      llex.o    lmem.o     lobject.o  lopcodes.o lparser.o  lstate.o  \
		  lstring.o  ltable.o  ltm.o      lundump.o  lvm.o      lzio.o     ltests.o  \
                                                                                     \
          lbaselib.o ldblib.o  liolib.o   lmathlib.o loslib.o   ltablib.o  lstrlib.o \
	      lutf8lib.o loadlib.o lcorolib.o linit.o                                    \
                                                                                     \
	      lauxlib.o

# fix vendored paths
LUA_T  := $(addprefix $(VENDOR_LUA_PREFIX),$(LUA_T))
LUA_O  := $(addprefix $(VENDOR_LUA_PREFIX),$(LUA_O))

ALL_O  := $(LUA_O) $(EH_O)
ALL_T  := $(LUA_T) $(EH_T)
ALL    := $(ALL_O) $(ALL_T) $(EH_E)

$(EH_E): $(ALL_T)
	$(CC) $^ -o $@

$(EH_T): $(EH_O)
	$(AR) $@ $^

$(LUA_T): $(LUA_O)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: eh eh-devel clean

eh: eh-devel

eh-devel:
	$(CC) $()

clean:
ifeq ($(OS),Windows_NT)
	del $(ALL) 2>nul
else
	rm $(ALL)
endif

.DEFAULT_GOAL := eh
