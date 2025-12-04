struct A{
	int i = 0;
	int return_inc() {
		return i + 1;
	}
};

signed main(){
	const A a;
	a.return_inc();
}
