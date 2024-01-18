//
// Created by Johny Georges on 2024-01-10.
//

#ifndef JETLANG_SYNTAX_ANALYZER_H
#define JETLANG_SYNTAX_ANALYZER_H

#include <stack>
#include "../../token/token-table.h"
#include "../../lexeme/lexeme.h"
#include "../../ast/ast.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "../lexical-analyzer/lexical-analyzer.h"

class SyntaxAnalyzer {
private:
    TokenTable* _tokenTable;
    AST* _ast;
    LexicalAnalyzer* _lexicalAnalyzer;
    std::stack<Lexeme> _stack;
    ASTFileNode _currentFileNode;
    std::optional<ASTNode*> _currentNode;
    void shift();
    void reduce();
    void accept();
    void error();
public:
    SyntaxAnalyzer(TokenTable* tokenTable, AST* ast, LexicalAnalyzer* lexicalAnalyzer);
    void analyze();
};

#endif //JETLANG_SYNTAX_ANALYZER_H
