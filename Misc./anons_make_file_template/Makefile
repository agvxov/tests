.PHONY: test clean
.SUFFIXES:

# --- Paths / files
SOURCE.d := source/
OBJECT.d := object/
LIB.d    := library/

SOURCE := main.c h.c cpp.cpp
OBJECT := ${SOURCE}
OBJECT := $(subst .cpp,.o,${OBJECT})
OBJECT := $(subst .c,.o,${OBJECT})

GENSOURCE := l.yy.c y.tab.c

vpath %.c ${SOURCE.d}
vpath %.l ${SOURCE.d}
vpath %.y ${SOURCE.d}
vpath %.cpp ${SOURCE.d}
vpath %.yy.c ${OBJECT.d}
vpath %.tab.c ${OBJECT.d}

OUT := example

# --- Tools/Flags
ifeq (${DEBUG}, 1)
  LFLAGS   += --debug --trace
  YFLAGS   += --debug

  CPPFLAGS += -DDEBUG

  CFLAGS.D += -Wall -Wextra -Wpedantic
  CFLAGS.D += -O0 -ggdb -fno-inline
  CFLAGS.D += -fsanitize=address,undefined
  CFLAGS   += ${CFLAGS.D}
  CXXFLAGS += ${CFLAGS.D}
else
  CFLAGS += -O3 -flto=auto -fno-stack-protector
endif

CPPFLAGS += -I${SOURCE.d} -I${OBJECT.d} -I${LIB.d}
LDLIBS := 

# --- Rule Section ---
all: ${OUT}

${OUT}: ${GENSOURCE} ${OBJECT}
	${LINK.c} -o $@ $(addprefix ${OBJECT.d}/,${OBJECT} ${GENSOURCE}) ${LDLIBS}

%.o: %.c
	${COMPILE.c} -o ${OBJECT.d}/$@ $<

%.o: %.cpp
	${COMPILE.c} -o ${OBJECT.d}/$@ $<

%.yy.c: %.l
	flex -o ${OBJECT.d}/$@ --header=${OBJECT.d}/$(subst .c,.h,$@) $? 

%.tab.c: %.y
	bison -o ${OBJECT.d}/$@ --header=${OBJECT.d}/$(subst .c,.h,$@) $? 

%.yy.o: ${OBJECT.d}/%.yy.c
	${COMPILE.c} -o $@ $<

%.tab.o: %.tab.c
	${COMPILE.c} -o $@ $<

test:
	cmdtest --fast

clean:
	-${RM} $(or ${OBJECT.d},#)/*
	-${RM} ${OUT}

# --- Notes ---
# I did not comment into the source so you may use it as a template easier.
#
# With `.SUFFIXES:`, we empty out the default rules
#  because they do not comply with our project structure.
#  They also have a tendency to delete intermediate files.
#  this is in good spirit as it could be a storage space concern,
#  however on modern systems and for reasonable projects
#  this behaviour is useless at best and annoying at worst.
#
# We make use of Make's support for variables with dots in their names,
#  because it helps a lot with readability.
#
# `vpath` helps us avoid `${SOURCE.d}/%.c` and such,
#   removing visual clutter. It also has nicer syntax than `VPATH`.
#
# We account for `DEBUG` being passed from the environment.
#  It's a very convenient way for toggling developer builds.
#
# `flex` and `bison` are explicitly specified,
#  because it is highly unlikely ${LEX} and ${YACC}
#  will be able to parse your source code;
#  not to mention that they are simply
#  the same tools pretending to be POSIX.
# Wherever no such concerns are present, we use the builtins.
#  Some people depend on this behaviour to get linting.
#
# We use $(or) to prevent anyone deleting their root
#  in case the definition of ${OBJECT.d} goes missing.
