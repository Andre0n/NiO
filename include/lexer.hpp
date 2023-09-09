#pragma once

#include "token.hpp"

#include <memory>
#include <string>
#include <vector>

class Lexer {
  private:
    bool at_end{false};
    std::string source{};
    std::size_t cursor{0};
    std::size_t line{0};
    std::size_t column{0};
    std::string literal{};
    char current{};

    std::vector<std::unique_ptr<Token>> tokens;

    auto advance() -> void;
    auto match_ahead(char expected) -> bool;
    auto tokenize_number() -> void;
    auto tokenize_word() -> void;

  public:
    Lexer(const std::string& p_source) : source(std::move(p_source)){};
    auto tokenize() -> std::vector<std::unique_ptr<Token>>;
};