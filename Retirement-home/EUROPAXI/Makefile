#!/usr/bin/make -f
# Don't fucking touch this without a good reason or I will fucking strangle you

CFLAGS   := -std=gnu23
CPPFLAGS := -Iinclude
LDFLAGS  := -lm

DEBUG := 1

ifeq (${DEBUG},1)
        CFLAGS += -Og -ggdb -pg -fno-inline -Wall -Wextra -Wpedantic -Wshadow -Wundef
else
        CFLAGS   += -O2 -flto=auto
        CPPFLAGS += -DNDEBUG -D_FORTIFY_SOURCE=2
endif

SOURCE.dir	:= source
OBJECT.dir	:= object
SOURCE.orig	:= $(wildcard ${SOURCE.dir}/*.c)
SOURCE.orig	:= $(SOURCE.orig:${SOURCE.dir}/%=%)
SOURCE		:= $(addprefix ${SOURCE.dir}/, $(SOURCE.orig))
OBJECT		:= $(addprefix ${OBJECT.dir}/, $(SOURCE.orig:.c=.o))

${OBJECT.dir}/%.o: ${SOURCE.dir}/%.c
	@echo "CC	$<"
	@${COMPILE.c} $(CPPFLAGS) -o $@ $<

all: EUROPA\|XI

clean:
	rm -f $(OBJECT) EUROPA\|XI

EUROPA|XI: $(OBJECT)
	@echo "LD	$@"
	@${LINK.c} -o "$@" $+ library/libraylib.amd64.a $(LDFLAGS)

library/libraylib.amd64.a:
	@rm -rf /tmp/raylib-5.5_linux_amd64
	wget -P /tmp/ "https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz"
	@tar xvC /tmp/ -f /tmp/raylib-5.5_linux_amd64.tar.gz \
	raylib-5.5_linux_amd64/lib/libraylib.a \
	raylib-5.5_linux_amd64/LICENSE \
	raylib-5.5_linux_amd64/include
	@cp -f /tmp/raylib-5.5_linux_amd64/lib/libraylib.a library/libraylib.amd64.a
	@cp -f /tmp/raylib-5.5_linux_amd64/include/* include/
	@cp -n /tmp/raylib-5.5_linux_amd64/LICENSE library/libraylib.LICENSE.a
