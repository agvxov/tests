ALSO        += ${OBJECT.dir}/libbox2d.a
OBJECT.orig += ${OBJECT.dir}/libbox2d.a .WAIT
CPPFLAGS    += -I${OBJECT.dir}/box2d/

${OBJECT.dir}/libbox2d.a: .peru/lastimports
	@cmake -DGLFW_BUILD_WAYLAND=OFF -B library/box2d -S library/box2d
	@cmake --build library/box2d
	@cp -r library/box2d/src/libbox2d.a library/box2d/include/box2d ${OBJECT.dir}
