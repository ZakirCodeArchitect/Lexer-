#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "header/lexer.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Please supply the source file" << std::endl;
        return 1;
    }

    std::cout << "Reading from file: " << argv[1] << std::endl;
    std::ifstream sourceFileStream(argv[1]);

    if (!sourceFileStream.is_open())
    {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    char temp;

    while (sourceFileStream.get(temp))
    {
        buffer << temp;
    }

    sourceFileStream.close(); // Optional, for clarity

    std::string sourceCode = buffer.str();

    std::cout << "This is the source code:" << std::endl
              << sourceCode << std::endl;

    Lexer lexer(sourceCode);

    // Tokenizing the source code and return bunch of tokens, pointers to the token basically.

    std::vector<Token *> tokens = lexer.tokenize();

    int counter = 0;

    std::cout << "TOKENIZED SUCCESSFULLY! \n"
              << std::endl;

    for (Token *temp : tokens)
    {
        counter++;
        std::cout << counter << "- " << temp->VALUE << " " << typeToString(temp->TYPE) << std::endl;
    }
    std::cout << "This is the end of the program" << std::endl;

    return 0;
}
