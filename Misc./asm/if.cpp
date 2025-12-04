//g++ if.cpp -std=c++17 -g
int main(int argc, char* argv[]){
    if(5 > ++argc){
        return 1;
    }
    return 2;
}