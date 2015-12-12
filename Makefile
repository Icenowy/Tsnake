NAMESPACES=-D_GNU_SOURCE

CC ?= gcc
CXX ?= g++
CXXLD ?= $(CXX)

HOSTCXX ?= $(CXX)

CFLAGS ?= -g
CXXFLAGS ?= -g

LDFLAGS ?=

LIBS ?= -lncurses

PREFIX ?= $(PWD)
LOCALEDIR ?= NULL

TSNAKE_OBJS=src/main.o src/game.o src/global_var.o src/handbook_txt.o src/handbook.o src/split.o src/cur_strutils.o

CFLAGS += -DPREFIX="\"$(PREFIX)\""
CXXFLAGS += -DPREFIX="\"$(PREFIX)\"" -DLOCALEDIR=$(LOCALEDIR)

all: tsnake

util/hbgen: util/hbgen.cpp
	$(HOSTCXX) util/hbgen.cpp -o util/hbgen

src/global_var.o: src/global_var.cpp src/global_var.h src/cur_strutils.h

src/main.o: src/main.cpp src/game.h src/global_var.h src/handbook.h src/cur_strutils.h src/tsgettext.h

src/game.o: src/game.cpp src/split.h src/game.h src/cur_strutils.h src/tsgettext.h

src/split.o: src/split.cpp src/split.h src/global_var.h src/cur_strutils.h

src/cur_strutils.o: src/cur_strutils.cpp src/cur_strutils.h

src/handbook_txt.o: src/handbook_txt.cpp src/handbook.h

src/handbook_txt.cpp: src/handbook.txt util/hbgen
	util/hbgen < src/handbook.txt > src/handbook_txt.cpp

tsnake: $(TSNAKE_OBJS)
	$(CXXLD) $(TSNAKE_OBJS) -o tsnake $(LIBS) $(LDFLAGS)
clean:
	rm -f $(TSNAKE_OBJS) tsnake src/handbook_txt.cpp util/hbgen
.PHONY: all clean
