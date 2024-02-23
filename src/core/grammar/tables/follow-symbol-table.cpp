//
// Created by Johny Georges on 2024-01-17.
//

#include "follow-symbol-table.h"

FollowSymbolTable::FollowSymbolTable() {
    _followSymbolMap = std::unordered_map<SymbolType, std::vector<SymbolType>*, std::hash<int>>();
    this->init();
}

bool FollowSymbolTable::isValidFollowSymbol(SymbolType followSymbolType, SymbolType symbolType) {
    auto viableFollowSymbols = _followSymbolMap.find(symbolType);
    if (viableFollowSymbols == _followSymbolMap.end()) {
        return false;
    }
    return std::find(viableFollowSymbols->second->begin(),
                     viableFollowSymbols->second->end(),
                     followSymbolType) != viableFollowSymbols->second->end();
}

void FollowSymbolTable::init() {
    this->add(SYM_CONST, new std::vector<SymbolType> {
        SYM_IDENTIFIER
    });
    this->add(SYM_LET, new std::vector<SymbolType> {
        SYM_IDENTIFIER
    });
    this->add(SYM_EQUAL, new std::vector<SymbolType> {
        SYM_IDENTIFIER,
        SYM_INT,
        SYM_FLOAT,
        SYM_CHAR,
        SYM_STRING,
        SYM_BANG,
        SYM_LEFT_PAREN,
        SYM_LEFT_BRACKET,
        SYM_MINUS
    });
    this->add(SYM_IDENTIFIER, new std::vector<SymbolType> {
        SYM_EQUAL,
        SYM_PLUS,
        SYM_MINUS,
        SYM_STAR,
        SYM_SLASH,
        SYM_MODULO,
        SYM_RIGHT_PAREN,
        SYM_RIGHT_BRACKET,
        SYM_COLON,
        SYM_COMMA,
        SYM_AND,
        SYM_OR,
        SYM_BANG_EQUAL,
        SYM_EQUAL_EQUAL,
        SYM_SEMICOLON
    });
    this->add(SYM_AND, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_STRING,
        SYM_CHAR,
        SYM_IDENTIFIER
    });
    this->add(SYM_OR, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_STRING,
        SYM_CHAR,
        SYM_IDENTIFIER
    });
    this->add(SYM_TRUE, new std::vector<SymbolType> {
        SYM_RIGHT_PAREN,
        SYM_RIGHT_BRACKET,
        SYM_COMMA,
        SYM_AND,
        SYM_OR,
        SYM_BANG_EQUAL,
        SYM_EQUAL_EQUAL,
        SYM_SEMICOLON
    });
    this->add(SYM_FALSE, new std::vector<SymbolType> {
        SYM_RIGHT_PAREN,
        SYM_RIGHT_BRACKET,
        SYM_COMMA,
        SYM_AND,
        SYM_OR,
        SYM_BANG_EQUAL,
        SYM_EQUAL_EQUAL,
        SYM_SEMICOLON
    });
    this->add(SYM_CHAR, new std::vector<SymbolType> {
        SYM_RIGHT_PAREN,
        SYM_RIGHT_BRACKET,
        SYM_COMMA,
        SYM_AND,
        SYM_OR,
        SYM_BANG_EQUAL,
        SYM_EQUAL_EQUAL,
        SYM_SEMICOLON
    });
    this->add(SYM_STRING, new std::vector<SymbolType> {
        SYM_PLUS,
        SYM_RIGHT_PAREN,
        SYM_RIGHT_BRACKET,
        SYM_COMMA,
        SYM_AND,
        SYM_OR,
        SYM_BANG_EQUAL,
        SYM_EQUAL_EQUAL,
        SYM_SEMICOLON
    });

    this->add(SYM_INT, new std::vector<SymbolType> {
            SYM_PLUS,
            SYM_MINUS,
            SYM_STAR,
            SYM_SLASH,
            SYM_MODULO,
            SYM_LESS_THAN,
            SYM_GREATER_THAN,
            SYM_RIGHT_PAREN,
            SYM_RIGHT_BRACKET,
            SYM_COMMA,
            SYM_AND,
            SYM_OR,
            SYM_BANG_EQUAL,
            SYM_EQUAL_EQUAL,
            SYM_SEMICOLON
    });

    this->add(SYM_FLOAT, new std::vector<SymbolType> {
            SYM_PLUS,
            SYM_MINUS,
            SYM_STAR,
            SYM_SLASH,
            SYM_MODULO,
            SYM_LESS_THAN,
            SYM_GREATER_THAN,
            SYM_RIGHT_PAREN,
            SYM_RIGHT_BRACKET,
            SYM_COMMA,
            SYM_AND,
            SYM_OR,
            SYM_BANG_EQUAL,
            SYM_EQUAL_EQUAL,
            SYM_SEMICOLON
    });

    this->add(SYM_PLUS, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_STRING,
        SYM_IDENTIFIER
    });

    this->add(SYM_MINUS, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_IDENTIFIER
    });

    this->add(SYM_MODULO, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_IDENTIFIER
    });

    this->add(SYM_STAR, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_IDENTIFIER
    });

    this->add(SYM_SLASH, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_IDENTIFIER
    });

    this->add(SYM_LESS_THAN, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_IDENTIFIER
    });

    this->add(SYM_GREATER_THAN, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_IDENTIFIER
    });

    this->add(SYM_LEFT_BRACKET, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_STRING,
        SYM_CHAR,
        SYM_IDENTIFIER
    });

    this->add(SYM_RIGHT_BRACKET, new std::vector<SymbolType> {
        SYM_PLUS,
        SYM_AND,
        SYM_OR,
        SYM_SEMICOLON
    });

    this->add(SYM_LEFT_BRACE, new std::vector<SymbolType> {
        SYM_IDENTIFIER,
    });

    this->add(SYM_RIGHT_BRACE, new std::vector<SymbolType> {
        SYM_SEMICOLON,
    });

    this->add(SYM_LEFT_PAREN, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_STRING,
        SYM_CHAR,
        SYM_IDENTIFIER,
    });

    this->add(SYM_RIGHT_PAREN, new std::vector<SymbolType> {
        SYM_PLUS,
        SYM_MINUS,
        SYM_STAR,
        SYM_SLASH,
        SYM_MODULO,
        SYM_AND,
        SYM_OR,
        SYM_RIGHT_BRACKET,
        SYM_BANG_EQUAL,
        SYM_EQUAL_EQUAL,
        SYM_SEMICOLON
    });

    this->add(SYM_BANG, new std::vector<SymbolType> {
        SYM_IDENTIFIER,
        SYM_LEFT_PAREN,
        SYM_TRUE,
        SYM_FALSE
    });

    this->add(SYM_BANG_EQUAL, new std::vector<SymbolType> {
        SYM_IDENTIFIER,
        SYM_INT,
        SYM_FLOAT,
        SYM_CHAR,
        SYM_STRING,
        SYM_TRUE,
        SYM_FALSE,
        SYM_BANG
    });

    this->add(SYM_SEMICOLON, new std::vector<SymbolType> {
        SYM_LET,
        SYM_CONST,
    });

    this->add(SYM_COLON, new std::vector<SymbolType> {
        SYM_INT,
        SYM_FLOAT,
        SYM_CHAR,
        SYM_STRING,
    });

    this->add(SYM_COMMA, new std::vector<SymbolType> {
            SYM_INT,
            SYM_FLOAT,
            SYM_CHAR,
            SYM_STRING,
            SYM_IDENTIFIER
    });

    this->add(SYM_PERIOD, new std::vector<SymbolType> {
            SYM_IDENTIFIER
    });

    this->add(SYM_MALFORMED, new std::vector<SymbolType> { });

}

void FollowSymbolTable::add(SymbolType symbol, std::vector<SymbolType>* followSymbols) {
    _followSymbolMap.insert(std::pair<SymbolType, std::vector<SymbolType>*>(symbol, followSymbols));
}