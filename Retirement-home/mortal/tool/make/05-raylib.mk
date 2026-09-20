ALSO        += ${OBJECT.dir}/libraylib.a
OBJECT.orig += ${OBJECT.dir}/libraylib.a .WAIT

${OBJECT.dir}/libraylib.a: .peru/lastimports
	@cmake -DBUILD_EXAMPLES=0 -DWITH_PIC=1 -DBUILD_SHARED_LIBS=0 -DCMAKE_BUILD_TYPE=make -B library/raylib -S library/raylib
	@cmake --build library/raylib
	@cp library/raylib/raylib/libraylib.a library/raylib/raylib/include/* ${OBJECT.dir}

# According to feedback, this is "intended" and has no way to fix without forking.

${OBJECT.dir}/rcamera.h.pch: CFLAGS += -include object/raylib.h.pch
${OBJECT.dir}/rcamera.h.pch: object/raylib.h.pch

${OBJECT.dir}/rcamera.h.gch: CFLAGS += -include object/raylib.h.gch
${OBJECT.dir}/rcamera.h.gch: object/raylib.h.gch
