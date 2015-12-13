CXX ?= g++
CXXLD ?= $(CXX)

HOSTCXX ?= $(CXX)

CXXFLAGS ?= -g

LDFLAGS ?=

LIBS ?= -lncurses -lm

PREFIX ?= $(PWD)
LOCALEDIR ?= $(PREFIX)/share/locale
BINDIR ?= $(PREFIX)/bin

TSNAKE_OBJS=src/main.o src/game.o src/global_var.o src/handbook_txt.o src/handbook.o src/split.o src/cur_strutils.o src/map.o src/map_gen.o src/snake.o src/mode_pause.o src/mode_end.o src/mode_play.o

PATHS = -DPREFIX="\"$(PREFIX)\"" -DLOCALEDIR="\"$(LOCALEDIR)\""
CXXSTD = -std=gnu++11

CXXFLAGS += $(PATHS) $(CXXSTD)

DESTDIR ?=

all: tsnake

util/hbgen: util/hbgen.cpp
	$(HOSTCXX) util/hbgen.cpp -o util/hbgen

src/global_var.o: src/global_var.cpp src/global_var.h src/cur_strutils.h

src/main.o: src/main.cpp src/game.h src/global_var.h src/handbook.h src/cur_strutils.h src/tsgettext.h src/snake.h src/const.h

src/game.o: src/game.cpp src/split.h src/game.h src/cur_strutils.h src/tsgettext.h src/map.h src/snake.h src/point.h src/mode_play.h src/mode_pause.h src/mode_end.h

src/split.o: src/split.cpp src/split.h src/global_var.h src/cur_strutils.h src/const.h

src/cur_strutils.o: src/cur_strutils.cpp src/cur_strutils.h

src/map.o: src/map.cpp src/map.h src/matrix.h src/global_var.h src/const.h

src/map_gen.o: src/map_gen.cpp src/map.h src/matrix.h src/global_var.h src/const.h

src/snake.o: src/snake.cpp src/snake.h src/map.h src/matrix.h src/point.h src/global_var.h src/const.h

src/mode_pause.o: src/mode_pause.cpp src/mode_pause.h src/mode_play.h src/game.h

src/mode_end.o: src/mode_end.cpp src/mode_end.h src/mode_play.h src/game.h src/const.h

src/mode_play.o: src/mode_play.cpp src/mode_play.h src/mode_end.h src/mode_pause.h src/game.h src/snake.h src/const.h

src/handbook_txt.o: src/handbook_txt.cpp src/handbook.h

src/handbook_txt.cpp: src/handbook.txt util/hbgen
	util/hbgen < src/handbook.txt > src/handbook_txt.cpp

tsnake: $(TSNAKE_OBJS)
	$(CXXLD) $(TSNAKE_OBJS) -o tsnake $(LIBS) $(LDFLAGS)

update-pot:
	sh po/update-pot.sh

%.mo: %.po
	msgfmt $< -o $@

install-mo: po/zh_CN.mo
	sh po/install-mo.sh "$(DESTDIR)$(LOCALEDIR)"

install-bin: tsnake
	mkdir -p "$(DESTDIR)$(BINDIR)/"
	install -m755 tsnake "$(DESTDIR)$(BINDIR)/"

install: install-mo install-bin

dependencies:
	sh util/install-dependencies.sh

clean:
	rm -f $(TSNAKE_OBJS) tsnake src/handbook_txt.cpp util/hbgen po/*.mo
.PHONY: all clean update-pot install-mo install-bin install dependencies
