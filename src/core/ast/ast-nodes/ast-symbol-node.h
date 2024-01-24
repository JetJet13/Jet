//
// Created by Johny Georges on 2024-01-23.
//

#ifndef JETLANG_AST_SYMBOL_NODE_H
#define JETLANG_AST_SYMBOL_NODE_H

#include "ast-node.h"

class ASTSymbolNode : public ASTNode {
private:
    Symbol* _symbol;
public:
    ASTSymbolNode(Symbol* symbol);
    Symbol* getSymbol();
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_SYMBOL_NODE_H
