// @COMPILECMD g++ $@ -o regex_error -std=c++20
#include <iostream>
#include <regex>

int main() {
    std::string input = "Hello world, this is a sample text with hello world.";

    std::regex pattern("+hello\\s+world", std::regex_constants::icase); // Case-insensitive regex pattern

    std::smatch matches;
    if (std::regex_search(input, matches, pattern)) {
        std::cout << "Found 'hello world' at position " << matches.position() << std::endl;
    } else {
        std::cout << "Pattern not found." << std::endl;
    }

    return 0;
}
