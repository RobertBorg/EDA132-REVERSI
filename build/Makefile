#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -Wall -W -ansi -pedantic -std=c++11
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
CC        = g++

# insert this line somewhere at the top of the file
DEBUG = false
# insert the following lines after the definitions of CXXFLAGS and LDFLAGS
ifeq ($(DEBUG), true)
	CXXFLAGS += -ggdb
	LDFLAGS += -ggdb
else
	CXXFLAGS += -O2
endif

NOOPT = false
ifeq ($(NOOPT), true)
	CXXFLAGS += -O2
endif

ALLTARGETS = reversi

VPATH= ../src/

sources = $(wildcard *.cc) $(notdir $(foreach dir,$(VPATH),$(wildcard $(dir)/*.cc)))

.PHONY: install uninstall all clean cleaner profile

all: $(ALLTARGETS)

%.dd: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


# Linking:
reversi: reversi.o algorithm.o

profile: reversi
	LD_PRELOAD="/usr/local/lib/libprofiler.so" CPUPROFILE=/tmp/mybin.prof ./reversi

# Dependencies, the implicit rule .cc => .o is used
include $(sources:.cc=.dd)

install: all
	mkdir -p lib bin
	cp $(ALLTARGETS) ./bin

uninstall:
	cd ./bin; rm $(ALLTARGETS)
 
clean:
	$(RM) *.o *.dd*

cleaner:
	$(RM) *.dd* *.o $(ALLTARGETS)
