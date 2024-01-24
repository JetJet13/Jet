//
// Created by Johny Georges on 2024-01-10.
//

#ifndef JETLANG_SYNTAX_ANALYZER_H
#define JETLANG_SYNTAX_ANALYZER_H

#include <vector>
#include "../../token/token-table.h"
#include "../../lexeme/lexeme.h"
#include "../../ast/ast.h"
#include "../../ast/ast-nodes/ast-file-node.h"
#include "../lexical-analyzer/lexical-analyzer.h"

/* This SyntaxAnalyzer is a LALR(1) parser that performs bottom-up parsing
 * Instructions:
 * 1. consume each token from left to right one by one with the option to look-ahead 1 token
 * 2. Push each token onto the handle stack
 * 2. create a handle composed of one or more tokens living on the stack
 * 3. check to see if the handle can be 'reduced' into an AST Node
 * 4. if it can, create the AST Node and push it to the state stack
 */

class SyntaxAnalyzer {
private:
    TokenTable* _tokenTable;
    ReservedKeywords* _reservedKeywords;
    LexicalAnalyzer* _lexicalAnalyzer;
    std::vector<Lexeme> _handle;
    std::vector<ASTNode*> _nodes;
    bool recognizeHandle();
    bool recognizeNodes();
    void shift();
    void reduceHandle();
    void reduceNodes();
    void accept();
    void error();
public:
    SyntaxAnalyzer(TokenTable* tokenTable, ReservedKeywords* reservedKeywords, LexicalAnalyzer* lexicalAnalyzer);
    void analyze();
};

#endif //JETLANG_SYNTAX_ANALYZER_H
