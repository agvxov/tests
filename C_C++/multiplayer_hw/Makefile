.PHONY: main clean

main: base.out screamer.out proto.out ser.out

base.out:
	bake base.c

screamer.out:
	bake screamer.c

proto.out:
	bake player.proto
	bake proto.c

ser.out:
	bake ser.c

clean:
	-${RM} base.out
	-${RM} screamer.out
	-${RM} player.pb-c.h player.pb-c.c
	-${RM} proto.out
	-${RM} player.cs.h player.cs.c
	-${RM} ser.out
