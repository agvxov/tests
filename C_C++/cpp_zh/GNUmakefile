.PHONY: clean run

ifeq (${DEBUG}, 1)
  LFLAGS   += --debug --trace
  CXXFLAGS += -Wall -Wextra -Wpedantic 
  CXXFLAGS += -DDEBUG -O0 -ggdb -fno-inline	
  WRAP     := valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all 
else
  CXXFLAGS += -O3 -fno-stack-protector
endif

OUT := a.out

SOURCE.d  := source/
OBJECT.d  := object/

HEADER  := Employee.hpp Worker.hpp Contractee.hpp Manager.hpp Company.hpp
HEADER  := $(addprefix ${SOURCE.d}/,${HEADER})
SOURCE  := main.cpp Employee.cpp Worker.cpp Contractee.cpp Manager.cpp Company.cpp
OBJECT  := $(addprefix ${OBJECT.d}/,${SOURCE})
OBJECT  := ${OBJECT:.cpp=.o}

${SOURCE.d}/%.cpp: ${SOURCE.d}/%.hpp

${OBJECT.d}/%.o: ${SOURCE.d}/%.cpp
	${COMPILE.cpp} -o $@ $<

${OUT}: ${HEADER} ${OBJECT}
	${LINK.cpp} -o $@ ${OBJECT} ${LDLIBS}

run: ${OUT}
	${WRAP} ./${OUT}

clean:
	-rm ${OUT}
	-rm ${OBJECT}
