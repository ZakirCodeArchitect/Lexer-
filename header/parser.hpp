#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.hpp"
#include "vector"

// NODES
enum NODE_TYPE
{
    NODE_ROOT, // ROOT NODE will be passed to assembly generator
    NODE_VARIABLE,
    NODE_RETURN,
    NODE_PRINT,
    NODE_INT
};

struct AST_NODE
{
    enum NODE_TYPE TYPE;
    std::string *VALUE;
    AST_NODE *CHILD;
    std::vector<AST_NODE *> SUB_STATEMENTS; // This is only for the root node.
};

class Parser
{
public:
    Parser(std::vector<Token *> tokens)
    {
        parserTokens = tokens;
        index = 0;
        limit = parserTokens.size();
        current = parserTokens.at(index);
    }

    Token *proceed(enum TokenType TYPE)
    {
        if (current->TYPE != TYPE)
        {
            std::cout << "[!] Syntax Error 1" << current->VALUE << std::endl;
            exit(1);
        }
        else
        {
            index++;
            current = parserTokens.at(index);
            return current;
        }
    }

    AST_NODE *parseINT()
    {
        if (current->TYPE != TOKEN_INT)
        {
            std::cout << "[!] Syntax Error 2" << current->VALUE << std::endl;
            exit(1);
        }

        AST_NODE *newNode = new AST_NODE();
        newNode->TYPE = NODE_INT;
        newNode->VALUE = &current->VALUE;
        proceed(TOKEN_INT);

        return newNode;
    }

    AST_NODE *parseID()
    {
        std::string *buffer = &current->VALUE;
        proceed(TOKEN_ID);
        proceed(TOKEN_EQUALS);

        AST_NODE *newNode = new AST_NODE();
        newNode->TYPE = NODE_VARIABLE;

        newNode->CHILD = parseINT();

        return newNode;
    }

    // AST_NODE *parseRETURN()
    // {
    //     proceed(TOKEN_KEYWORD);
    //     AST_NODE *newNode = new AST_NODE;
    //     newNode->TYPE = NODE_RETURN;
    //     newNode->CHILD = parseINT();

    //     return newNode;
    // }

    AST_NODE *parseRETURN()
    {
        proceed(TOKEN_KEYWORD); // Expect 'return'
        AST_NODE *newNode = new AST_NODE;
        newNode->TYPE = NODE_RETURN;

        // Modify this to handle an identifier (variable), not just an integer
        if (current->TYPE == TOKEN_ID)
        {
            AST_NODE *childNode = new AST_NODE();
            childNode->TYPE = NODE_VARIABLE;    // Variable type for identifiers
            childNode->VALUE = &current->VALUE; // Store the variable name
            newNode->CHILD = childNode;
            proceed(TOKEN_ID); // Move past the identifier
        }
        else
        {
            std::cout << "[!] Syntax Error: Expected variable (identifier) after 'return' at line " << index << std::endl;
            exit(1);
        }

        return newNode;
    }

    AST_NODE *parsePRINT()
    {
        proceed(TOKEN_KEYWORD); // Expect 'print'
        AST_NODE *newNode = new AST_NODE;
        newNode->TYPE = NODE_PRINT;

        proceed(TOKEN_LEFT_PAREN); // Expect '('

        if (current->TYPE == TOKEN_STRING || current->TYPE == TOKEN_INT)
        {
            AST_NODE *childNode = new AST_NODE();
            childNode->TYPE = NODE_INT; // Reuse type as it's generic here
            childNode->VALUE = &current->VALUE;
            newNode->CHILD = childNode;
            proceed(current->TYPE); // Proceed past string or int
        }
        else
        {
            std::cout << "[!] SYNTAX ERROR: Expected STRING or INT after 'print(' at line " << index << std::endl;
            exit(1);
        }

        proceed(TOKEN_RIGHT_PAREN); // Expect ')'

        return newNode;
    }

    AST_NODE *parseKEYWORD()
    {
        if (current->VALUE == "return")
        {
            return parseRETURN(); // Handles 'return'
        }
        else if (current->VALUE == "print")
        {
            return parsePRINT(); // Correctly calls 'parsePRINT' for 'print'
        }
        else
        {
            std::cout << "[!] SYNTAX ERROR: UNDEFINED KEYWORD '" << current->VALUE << "' on line: " << index << std::endl;
            exit(1);
        }
    }

    AST_NODE *parse()
    {
        AST_NODE *ROOT = new AST_NODE();
        ROOT->TYPE = NODE_ROOT;

        while (current->TYPE != TOKEN_EOF)
        {
            switch (current->TYPE)
            {
            case TOKEN_ID:
            {
                ROOT->SUB_STATEMENTS.push_back(parseID());
                break;
            }
            case TOKEN_KEYWORD:
            {
                ROOT->SUB_STATEMENTS.push_back(parseKEYWORD());
                break;
            }
            default:
            {
                std::cout << "[!] Syntax Error 3" << current->VALUE << std::endl;
                exit(1);
            }
            }
            proceed(TOKEN_SEMICOLON);
        }
        return ROOT;
    }

private:
    int limit;
    int index;

    Token *current; // a pointer to token
    std::vector<Token *> parserTokens;
};

#endif
