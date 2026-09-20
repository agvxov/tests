ALSO        += ${OBJECT.dir}/libchad.a
OBJECT.orig += ${OBJECT.dir}/libchad.a .WAIT
#       **** EXTERNAL INCLUDE ROUTING ****
# WILL NOT PCH IF WE EVER FIX THAT TO BE RECURSIVE
CPPFLAGS    += -Ilibrary/libchad/

${OBJECT.dir}/libchad.a: .peru/lastimports
	@make -C library/libchad
	@cp library/libchad/object/libchad.a ${OBJECT.dir}

${OBJECT.dir}/rcamera.h.pch: CFLAGS += --include object/raylib.h
