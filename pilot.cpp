#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "./header/lexer.hpp"
#include "./header/parser.hpp"

int main(int argc, char **argv)
{
    // Check if a source file argument is provided
    if (argc < 2)
    {
        std::cout << "Please supply the source file" << std::endl;
        return 1;
    }

    // File being read
    std::cout << "Reading from file: " << argv[1] << std::endl;

    // open the source code file
    std::ifstream sourceFileStream(argv[1]);
    if (!sourceFileStream.is_open())
    {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    char temp;
    // reading content and storing in buffer
    while (sourceFileStream.get(temp))
    {
        buffer << temp;
    }
    sourceFileStream.close();

    // string stream to string -> source code
    std::string sourceCode = buffer.str();
    std::cout << "This is the source code:\n"
              << sourceCode << std::endl;

    // Initialize the lexer
    Lexer lexer(sourceCode);
    std::vector<Token *> tokens = lexer.tokenize();

    // Display tokens
    int counter = 0;
    std::cout << "\nTOKENIZED SUCCESSFULLY!\n";
    if (tokens.back()->TYPE != TOKEN_EOF)
    {
        Token *EOFNode = new Token();
        EOFNode->TYPE = TOKEN_EOF;
        tokens.push_back(EOFNode);
    }
    for (Token *temp : tokens)
    {
        counter++;
        std::cout << counter << "- " << temp->VALUE << " (" << typeToString(temp->TYPE) << ")\n";
    }

    Parser parser(tokens);
    AST_NODE *ROOT = parser.parse();

    std::cout << "Program execution completed." << std::endl;

    return 0;
}
