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
        advance();
    }
    auto token = std::make_unique<Token>(
        TokenType::_int, source.substr(start, cursor), line, start);
    tokens.emplace_back(std::move(token));
}

auto Lexer::tokenize_word() -> void {
    auto start{column};
    advance();
    while (std::isalnum(current) || current == '_') {
        advance();
    }

    auto token = std::make_unique<Token>(
        TokenType::_word, source.substr(start, cursor), line, start);
    tokens.emplace_back(std::move(token));
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
                                                source.substr(cursor, 1), line,
                                                column);
                break;
            }
            case ')': {
                token = std::make_unique<Token>(TokenType::close_paren,
                                                source.substr(cursor, 1), line,
                                                column);
                break;
            }
            case ';': {
                token = std::make_unique<Token>(
                    TokenType::semi, source.substr(cursor, 1), line, column);
                break;
            }
            case '+': {
                token = std::make_unique<Token>(
                    TokenType::plus, source.substr(cursor, 1), line, column);
                break;
            }
            default: {
                token = std::make_unique<Token>(
                    TokenType::_error, source.substr(cursor, 1), line, column);
                break;
            }
            }
            tokens.emplace_back(std::move(token));
            advance();
        }
    }
    return std::move(tokens);
};