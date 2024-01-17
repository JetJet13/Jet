//
// Created by Johny Georges on 2024-01-10.
//

#ifndef JETLANG_SYNTAX_ANALYZER_H
#define JETLANG_SYNTAX_ANALYZER_H

#include "../../token/token-table.h"
#include "../../lexeme/lexeme.h"
#include "../../ast/ast.h"
#include "../../ast/ast-nodes/ast-file-node.h"

class SyntaxAnalyzer {
private:
    TokenTable* _tokenTable;
    AST* _ast;
    ASTFileNode _currentFileNode;
    std::optional<ASTNode*> _currentNode;
    void initCurrentNode(Lexeme* lexeme);
public:
    SyntaxAnalyzer(TokenTable* tokenTable, AST* ast);
    void analyze(Lexeme* lexeme);
};

#endif //JETLANG_SYNTAX_ANALYZER_H
