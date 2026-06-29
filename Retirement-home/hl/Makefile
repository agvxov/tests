.PHONY: test clean
.SUFFIXES:

# --- Paths / files
SOURCE.d := source/
OBJECT.d := object/
LIB.d	 := library/

SOURCE := main.cpp hl.cpp
OBJECT := ${SOURCE}
OBJECT := $(subst .cpp,.o,${OBJECT})
OBJECT := $(subst .c,.o,${OBJECT})

GENSOURCE := vimhl.yy.c regex.yy.cpp
GENOBJECT := ${GENSOURCE}
GENOBJECT := $(subst .cpp,.o,${GENOBJECT})
GENOBJECT := $(subst .c,.o,${GENOBJECT})

vpath %.o ${OBJECT.d}
vpath %.c ${SOURCE.d}
vpath %.l ${SOURCE.d}
vpath %.cpp ${SOURCE.d}
vpath %.yy.c ${OBJECT.d}

OUT := hl

# --- Tools/Flags
ifeq (${DEBUG}, 1)
  LFLAGS   += --debug --trace

  CPPFLAGS += -DDEBUG

  CFLAGS.D += -Wall -Wextra -Wpedantic
  CFLAGS.D += -O0 -ggdb -fno-inline
  #CFLAGS.D += -fsanitize=address,undefined
  CFLAGS   += ${CFLAGS.D}
  CXXFLAGS += ${CFLAGS.D}
else
  CFLAGS += -O3 -flto=auto -fno-stack-protector
endif

CFLAGS   += -std=c2x
CPPFLAGS += -std=c++20
CPPFLAGS += -I${SOURCE.d} -I${OBJECT.d} -I${LIB.d}
LDLIBS   := -ldictate -lpcre2-8

# --- Rule Section ---
all: ${OUT}

${OUT}: ${GENSOURCE} ${GENOBJECT} ${OBJECT}
	${LINK.cpp} -o $@ $(addprefix ${OBJECT.d}/,${OBJECT} ${GENOBJECT}) ${LDLIBS}

%.o: %.c
	${COMPILE.c} -o ${OBJECT.d}/$@ $<

%.o: %.cpp
	${COMPILE.cpp} -o ${OBJECT.d}/$@ $<

%.yy.c: %.l
	flex ${LFLAGS} -o ${OBJECT.d}/$@ $? 

%.yy.cpp: %.l
	flex ${LFLAGS} -o ${OBJECT.d}/$@ $? 

%.yy.o: %.yy.c
	${COMPILE.c} -o ${OBJECT.d}/$@ ${OBJECT.d}/$< -fpermissive

%.yy.o: %.yy.cpp
	${COMPILE.cpp} -o ${OBJECT.d}/$@ ${OBJECT.d}/$<

test:
	cmdtest --fast

clean:
	-${RM} $(or ${OBJECT.d},#)/*
	-${RM} ${OUT}
