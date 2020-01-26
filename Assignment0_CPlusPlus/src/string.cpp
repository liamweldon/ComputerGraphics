#include <iostream>
#include <string>

int main() {

    std::string fullName = "Mike Shah";


    std::string firstName = fullName.substr(0, 4);
    std::string lastName = fullName.substr(5, 9);
    
    
    std::cout << "First: " << firstName << std::endl;
    std::cout << "Last: " << lastName << std::endl;


    unsigned int i = 0;
    while (i < fullName.length()) {
        if (fullName.at(i) == ' ') {
            break;
        }
        std::cout << fullName[i];
        ++i;
    }


    return 0;
}