# The NiO Lexer

The lexer scans the source code character by character and groups characters into tokens based on predefined rules.

## The current rules of lexer

-   Ignoring Whitespace
-   Identifying words
-   Handling Integer Literals

## Basic Lexer definition

To complete implementation see `src/lexer.cpp` and `include/lexer.hpp`

```cpp
 private:
    auto advance() -> void;
    auto match_ahead(char expected) -> bool;
    auto tokenize_number() -> void;
    auto tokenize_word() -> void;

  public:
    Lexer(const std::string& p_source) : source(std::move(p_source)){};
    auto tokenize() -> std::vector<std::unique_ptr<Token>>;
```

`advance` function moves the cursor forward while it is not at the end and check if is a new line too.

`match_ahead` function check if the next character is a expected character.

`tokenize_number` function generate an integer token for now; later, we can parse floats too.

`tokenize_word` function is similar to `tokenize_number`, but it's used for [words](gramar.md).
