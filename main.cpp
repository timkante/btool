#include <iostream>
#include "Parser.hpp"



int main() {

    Parser parser = Parser("","",TranslationTable("..\\src\\translationTable.json"));

    std::cout << "Ordner angeben\n";
    std::string path;
    std::cin >> path;

    parser.parseFiles(path);
    return 0;
}