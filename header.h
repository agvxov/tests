#define FUNSIZE 32
int fun(){
	int a[FUNSIZE];
	int r = 0;
	for(int i = 0; i < FUNSIZE;){
		r += a[i];
		i++;
	}
	return r;
}
