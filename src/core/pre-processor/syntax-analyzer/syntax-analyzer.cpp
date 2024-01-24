//
// Created by Johny Georges on 2024-01-10.
//

#include "syntax-analyzer.h"
#include "../../ast/ast-nodes/ast-symbol-node.h"
#include "../../ast/ast-nodes/ast-identifier-node.h"

SyntaxAnalyzer::SyntaxAnalyzer(TokenTable *tokenTable, ReservedKeywords* reservedKeywords, LexicalAnalyzer* lexicalAnalyzer) {
    _tokenTable = tokenTable;
    _reservedKeywords = reservedKeywords;
    _handle = std::vector<Lexeme>();
    _lexicalAnalyzer = lexicalAnalyzer;
    _nodes = std::vector<ASTNode*>();
}

void SyntaxAnalyzer::analyze() {

    while (true) {
        if (this->recognizeNodes()) {
            this->reduceNodes();
        } else if (this->recognizeHandle()) {
            this->reduceHandle();
        } else {
            this->shift();
        }

        if (!_lexicalAnalyzer->hasMore()) {
            _handle.empty() ? this->accept() : this->error();
            break;
        }
    }
}

bool SyntaxAnalyzer::recognizeHandle() {
    if (_handle.empty()) {
        return false;
    } else if (_handle.size() == 1) {
        auto lexeme = _handle[0];
        if (lexeme.getToken()->getSymbol()->isIdentifier() ||
            _reservedKeywords->isKeywordSymbol(lexeme.getToken()->getSymbol())) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

bool SyntaxAnalyzer::recognizeNodes() {
    if (_nodes.empty()) {
        return false;
    }
    return true;
}

void SyntaxAnalyzer::shift() {
    auto nextLexeme = _lexicalAnalyzer->next();
    if (nextLexeme) {
        _handle.push_back(nextLexeme.value());
    }
}

void SyntaxAnalyzer::reduceHandle() {
    if (_handle.size() == 1) {
        auto lexeme = _handle[0];
        if (lexeme.getToken()->getSymbol()->isIdentifier()) {
            _nodes.push_back(new ASTIdentifierNode(&lexeme));
        } else {
            _nodes.push_back(new ASTSymbolNode(lexeme.getToken()->getSymbol()));
        }
    }
    _handle.clear();
}

void SyntaxAnalyzer::accept() {

}

void SyntaxAnalyzer::error() {

}

void SyntaxAnalyzer::reduceNodes() {
    if (_nodes.empty()) {
        return;
    }
}
