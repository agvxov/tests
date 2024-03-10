typedef struct {
	int i;
	int h;
} thing;

int queryi(thing t){
	return t.i;
}

int queryh(thing t){
	return t.h;
}

thing * newthing(){
	thing * t = (thing *)malloc(sizeof(thing));
	*t = (thing){
		.i = 0,
		.h = 0,
	};
	return t;
}
