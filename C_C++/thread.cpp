#include <iostream>
#include <unistd.h>
#include <thread>

bool asd = 1;
bool basd = 1;

void long_task(std::string stuff){
    while(asd){
        std::cout << "Doing 1 " << stuff << "..." << std::endl;
        sleep(1);
    }
}

void short_task(std::string stuff){
    while(basd){
        std::cout << "Doing 2 " << stuff << "..." << std::endl;
        sleep(1);
    }
}
int main() {
    std::thread a(long_task, "this");
    std::thread b(short_task, "this");

    std::cout << a.get_id() << std::endl << a.hardware_concurrency() << std::endl;

    sleep(2);
    basd = 0;

    b.join();

    sleep(5);
    asd = 0;

    a.join();

    std::cout << "\nDone.\n";

    return 0;
}
