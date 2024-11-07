# 📝 **MiniLang Lexical Analyzer (Lexer)**

> A simple lexical analyzer (lexer) designed to process and tokenize source code written in MiniLang, a hypothetical programming language used for compiler construction coursework. This lexer serves as the first step in building a full compiler for MiniLang.

---

## 🚀 **Project Overview**

MiniLang is a simplified programming language created for educational purposes in compiler construction. The **MiniLang Lexer** is designed to read MiniLang source code, tokenize it, and classify each token into its corresponding type (e.g., keywords, operators, identifiers, literals).

**Key Features:**
- **Token Classification:** Identifies and classifies tokens such as keywords, operators, identifiers, literals, and delimiters.
- **Error Handling:** Includes basic error handling for unrecognized tokens and invalid characters.
- **Comment Skipping:** Skips over single-line comments and excludes them from the token output.
- **Testing:** Provides sample valid and invalid MiniLang code to test the lexer’s functionality.

---

## 🌟 **MiniLang Features**

MiniLang includes the following types of tokens:

- **Keywords:** `if`, `else`, `while`, `print`, `int`, `float`
- **Operators:** `+`, `-`, `*`, `/`, `=`, `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Delimiters:** `(`, `)`, `{`, `}`, `;`, `,`
- **Identifiers:** Variable names that start with a letter, followed by letters or digits (e.g., `var1`, `total`)
- **Literals:** Integer literals (e.g., `123`), floating-point literals (e.g., `45.67`), and string literals enclosed in double quotes (e.g., `"Hello World"`)
- **Comments:** Single-line comments starting with `//` (which are ignored during tokenization)

---

## 🔧 **Installation**

To get started with the project locally, follow these steps:

### 1. Clone the repository:

```bash
git clone https://github.com/yourusername/minilang-lexer.git
cd minilang-lexer
```
## 🧑‍💻 **Usage**

To use the **MiniLang Lexer**, you need to provide it with a MiniLang source code file. The lexer will process the file, classify each token, and output the tokens in the following format:


Where `token_type` represents the type of the token (e.g., `KEYWORD`, `OPERATOR`, `IDENTIFIER`, `LITERAL`, etc.), and `lexeme` is the exact string or value of the token.

### Steps to Run:

1. Compile the project:

```bash
g++ -o lexer lexer.cpp
./lexer input.minilang

int x = 10;
if (x > 5) {
    print("Hello World");
}

```
---

### Key points:
- **Usage section** includes the commands for compiling and running the lexer.
- **Sample Output** shows an example of how the lexer outputs tokenized MiniLang code.
- It clearly explains each part of the output to make it easy for users to understand how their code is processed.


