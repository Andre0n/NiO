#include "lexer.hpp"
#include "token.hpp"

#include <memory>

auto Lexer::advance() -> void {
    cursor += 1;
    column += 1;
    if (cursor < source.size()) {
        current = source.at(cursor);
        if (current == '\n') {
            line += 1;
        }
    } else {
        at_end = true;
    }
}

auto Lexer::match_ahead(char expected) -> bool {
    if (cursor + 1 < source.size()) {
        return source.at(cursor + 1) == expected;
    }
    return false;
};

auto Lexer::tokenize_number() -> void {
    auto start{column};
    while (std::isdigit(current)) {
        literal += current;
        advance();
    }
    auto token = std::make_unique<Token>(TokenType::_int, literal, line, start);
    tokens.emplace_back(std::move(token));
    literal.clear();
}

auto Lexer::tokenize_word() -> void {
    auto start{column};

    literal += current;
    advance();

    while (std::isalnum(current) || current == '_') {
        literal += current;
        advance();
    }

    auto token =
        std::make_unique<Token>(TokenType::_word, literal, line, start);
    tokens.emplace_back(std::move(token));
    literal.clear();
}

auto Lexer::tokenize() -> std::vector<std::unique_ptr<Token>> {
    current = source.at(cursor);
    while (!at_end) {
        if (std::isspace(current)) {
            advance();
        } else if (std::isdigit(current)) {
            tokenize_number();
        } else if (std::isalpha(current) || current == '_') {
            tokenize_word();
        } else {
            std::unique_ptr<Token> token;
            switch (current) {
            case '(': {
                token = std::make_unique<Token>(TokenType::open_paren,
                                                std::string(1, current), line,
                                                column);
                break;
            }
            case ')': {
                token = std::make_unique<Token>(TokenType::close_paren,
                                                std::string(1, current), line,
                                                column);
                break;
            }
            case ';': {
                token = std::make_unique<Token>(
                    TokenType::semi, std::string(1, current), line, column);
                break;
            }
            case '+': {
                token = std::make_unique<Token>(
                    TokenType::plus, std::string(1, current), line, column);
                break;
            }
            default: {
                token = std::make_unique<Token>(
                    TokenType::_error, std::string(1, current), line, column);
                break;
            }
            }
            tokens.emplace_back(std::move(token));
            advance();
        }
    }
    return std::move(tokens);
};