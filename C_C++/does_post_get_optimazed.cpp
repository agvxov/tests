void for1(){
    for(int i = 0; i < 10; i++){
        ;
    }
}

void for2(){
    for(int i = 0; i < 10; ++i){
        ;
    }
}

int main(){

    for1();
    for2();

    return 0;
}