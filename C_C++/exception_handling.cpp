#include <iostream>
#include <string>

using namespace std;

int main(){

    int num;
    int i = 1;
    string mystring;

    cin >> mystring;

    try{
        i++;
        num = stoi(mystring);
        printf("mystring / 2 is %i", (num / 2));
    }
    catch(invalid_argument x){
        cout << "\ninvalid input!\n";
    }

    cout << i;

    return 0;
}