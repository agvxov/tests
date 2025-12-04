#include <iostream>
#include <signal.h>

using namespace std;

void handle_signal(){
    cout << "yay";
    abort();
}


int main(){

    signal(SIGINT, handle_signal)

    while(1){
        
    }

    return 0;
}