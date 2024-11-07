#ifndef __LEXER_H
#define __LEXER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

// Enum for token types
enum type
{
    TOKEN_ID,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_KEYWORD,
    TOKEN_PRINT,
    TOKEN_MINUS,
    TOKEN_PLUS,
    TOKEN_REL_NOTEQUALS,
    TOKEN_REL_EQUALS,
    TOKEN_REL_GREATERTHANEQUALS,
    TOKEN_REL_LESSTHANEQUALS,
    TOKEN_DIVIDE,
    TOKEN_TIMES,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_STRING,
    TOKEN_EQUALS,
    TOKEN_SEMICOLON,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_COMMA,
    TOKEN_REL_LESSTHAN,
    TOKEN_REL_GREATERTHAN,
};

// Structure for Tokens
struct Token
{
    enum type TYPE;
    std::string VALUE;
};

// Token type to strings
std::string typeToString(enum type TYPE)
{
    switch (TYPE)
    {
    case TOKEN_ID:
        return "IDENTIFIER";
    case TOKEN_INT:
        return "LITERAL";
    case TOKEN_FLOAT:
        return "LITERAL";
    case TOKEN_KEYWORD:
    case TOKEN_PRINT:
    case TOKEN_IF:
    case TOKEN_ELSE:
    case TOKEN_WHILE:
        return "KEYWORD";
    case TOKEN_MINUS:
    case TOKEN_PLUS:
    case TOKEN_REL_NOTEQUALS:
    case TOKEN_REL_EQUALS:
    case TOKEN_REL_GREATERTHANEQUALS:
    case TOKEN_REL_LESSTHANEQUALS:
    case TOKEN_DIVIDE:
    case TOKEN_TIMES:
    case TOKEN_REL_GREATERTHAN:
    case TOKEN_REL_LESSTHAN:
        return "OPERATOR";
    case TOKEN_LEFT_PAREN:
    case TOKEN_RIGHT_PAREN:
    case TOKEN_LEFT_BRACE:
    case TOKEN_RIGHT_BRACE:
    case TOKEN_COMMA:
    case TOKEN_SEMICOLON:
        return "DELIMITER";
    case TOKEN_STRING:
        return "STRING";
    case TOKEN_EQUALS:
        return "OPERATOR";
    default:
        return "UNRECOGNIZED_TOKEN";
    }
}

// lexer class
class Lexer
{
public:
    Lexer(std::string sourceCode) : source(sourceCode), cursor(0), size(sourceCode.length()), lineNumber(1), characterNumber(1)
    {
        current = source[cursor];
    }

    // advnace the cursor
    char advance()
    {
        if (cursor < size)
        {
            char temp = current;
            cursor++;
            characterNumber++;
            current = (cursor < size) ? source[cursor] : '\0'; // eof
            return temp;
        }
        return '\0';
    }

    // for spaces
    void checkAndSkip()
    {
        while (current == ' ' || current == '\n' || current == '\t')
        {
            if (current == '\n')
            {
                lineNumber++;
                characterNumber = 0;
            }
            advance();
        }
    }

    void skipComment()
    {
        while (current != '\n' && current != '\0')
        {
            advance();
        }
    }
    // delimeters and operators
    Token *tokenizeSpecial(enum type TYPE)
    {
        Token *newToken = new Token();
        newToken->TYPE = TYPE;
        newToken->VALUE = std::string(1, advance());
        return newToken;
    }

    Token *tokenizeKeywordOrIdentifier()
    {
        std::stringstream buffer;
        while (isalpha(current))
        {
            buffer << advance();
        }

        std::string keyword = buffer.str();
        Token *newToken = new Token();

        // Recognize keywords
        if (keyword == "if")
            newToken->TYPE = TOKEN_IF;
        else if (keyword == "else")
            newToken->TYPE = TOKEN_ELSE;
        else if (keyword == "while")
            newToken->TYPE = TOKEN_WHILE;
        else if (keyword == "print")
            newToken->TYPE = TOKEN_PRINT;
        else if (keyword == "int" || keyword == "float")
            newToken->TYPE = TOKEN_KEYWORD;
        else
            newToken->TYPE = TOKEN_ID; // Default to identifier if not a keyword

        newToken->VALUE = keyword;
        return newToken;
    }

    Token *tokenizeLiterals()
    {
        std::stringstream buffer;
        bool hasDecimal = false;

        while (isdigit(current) || (current == '.' && !hasDecimal))
        {
            if (current == '.')
            {
                hasDecimal = true;
            }
            buffer << advance();
        }

        Token *newToken = new Token();
        newToken->TYPE = hasDecimal ? TOKEN_FLOAT : TOKEN_INT;
        newToken->VALUE = buffer.str();
        return newToken;
    }

    Token *tokenizeString()
    {
        std::stringstream buffer;
        advance(); // Consume the opening quote (")
        while (current != '"' && current != '\0')
        {
            buffer << current;
            advance();
        }
        if (current == '"')
        {
            advance(); // Consume the closing quote (")
        }
        else
        {
            std::cerr << "Error: Unterminated string literal at line " << lineNumber << std::endl;
            return nullptr;
        }
        Token *newToken = new Token();
        newToken->TYPE = TOKEN_STRING;
        newToken->VALUE = buffer.str();
        return newToken;
    }

    Token *tokenizeOperatorOrDelimiter()
    {
        switch (current)
        {
        case '+':
            return tokenizeSpecial(TOKEN_PLUS);
        case '-':
            return tokenizeSpecial(TOKEN_MINUS);
        case '*':
            return tokenizeSpecial(TOKEN_TIMES);
        case '/':
            if (peak() == '/')
            {
                skipComment();
                return nullptr;
            }
            return tokenizeSpecial(TOKEN_DIVIDE);
        case '=': // ==
            if (peak() == '=')
            {
                advance();
                return tokenizeSpecial(TOKEN_REL_EQUALS);
            }
            return tokenizeSpecial(TOKEN_EQUALS);
        case '!':
            if (peak() == '=')
            {
                advance();
                return tokenizeSpecial(TOKEN_REL_NOTEQUALS);
            }
            break;
        case '<':
            if (peak() == '=')
            {
                advance();
                return tokenizeSpecial(TOKEN_REL_LESSTHANEQUALS);
            }
            return tokenizeSpecial(TOKEN_REL_LESSTHAN);
        case '>':
            if (peak() == '=')
            {
                advance();
                return tokenizeSpecial(TOKEN_REL_GREATERTHANEQUALS);
            }
            return tokenizeSpecial(TOKEN_REL_GREATERTHAN);
        case ',':
            return tokenizeSpecial(TOKEN_COMMA);
        case ';':
            return tokenizeSpecial(TOKEN_SEMICOLON);
        case '(':
            return tokenizeSpecial(TOKEN_LEFT_PAREN);
        case ')':
            return tokenizeSpecial(TOKEN_RIGHT_PAREN);
        case '{':
            return tokenizeSpecial(TOKEN_LEFT_BRACE);
        case '}':
            return tokenizeSpecial(TOKEN_RIGHT_BRACE);
        default:
            std::cerr << "Unrecognized character at line " << lineNumber << std::endl;
            advance();
            return nullptr;
        }
        return nullptr;
    }

    // To generate the list of tokens of the source code
    std::vector<Token *> tokenize()
    {
        std::vector<Token *> tokens;
        while (cursor < size)
        {
            checkAndSkip(); // Skip whitespace and newline characters

            if (current == '/' && peak() == '/')
            {
                skipComment(); // Skip single-line comments
                continue;
            }

            if (current == '"')
            {
                tokens.push_back(tokenizeString()); // Check for string literal
                continue;
            }

            if (isalpha(current) || current == '_')
            {
                tokens.push_back(tokenizeKeywordOrIdentifier()); // Check for identifier or keyword
                continue;
            }

            if (isdigit(current))
            {
                tokens.push_back(tokenizeLiterals()); // Check for literals (integers and floats)
                continue;
            }

            // Handle operators and delimiters
            Token *token = tokenizeOperatorOrDelimiter();
            if (token != nullptr)
                tokens.push_back(token);
        }
        return tokens;
    }

private:
    char current;
    size_t cursor;
    size_t size;
    int lineNumber;
    int characterNumber;
    std::string source;

    char peak()
    {
        return (cursor + 1 < size) ? source[cursor + 1] : '\0';
    }
};

#endif
