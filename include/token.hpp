#pragma once

#include <string>
#include <string_view>

enum class TokenType {
    _error = -2,
    _eof,
    _int,
    _word,
    plus,
    open_paren,
    close_paren,
    semi,
};

class Token {
  private:
    TokenType type;
    std::string_view value;
    struct {
        std::size_t line;
        std::size_t column;
    } loc;

  public:
    Token();
    Token(TokenType p_type, std::string_view p_value, std::size_t p_line,
          std::size_t p_column)
        : type(p_type), value(std::move(p_value)), loc{p_line, p_column} {};

    auto to_string() -> std::string_view { return value; };
};