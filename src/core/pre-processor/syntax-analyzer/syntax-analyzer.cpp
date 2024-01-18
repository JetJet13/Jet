//
// Created by Johny Georges on 2024-01-10.
//

#include "syntax-analyzer.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"


SyntaxAnalyzer::SyntaxAnalyzer(TokenTable *tokenTable, AST* ast, LexicalAnalyzer* lexicalAnalyzer) {
    _tokenTable = tokenTable;
    _ast = ast;
    _stack = std::stack<Lexeme>();
    _lexicalAnalyzer = lexicalAnalyzer;
    _currentFileNode = ASTFileNode();
    _currentNode = {};
}

void SyntaxAnalyzer::analyze() {
    if (_stack.empty()) {
        this->shift();
    }
}

void SyntaxAnalyzer::shift() {
    auto nextLexeme = _lexicalAnalyzer->next();
    if (nextLexeme) {
        _stack.push(nextLexeme.value());
    }
}

void SyntaxAnalyzer::reduce() {

}

void SyntaxAnalyzer::accept() {

}

void SyntaxAnalyzer::error() {

}
