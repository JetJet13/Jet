//
// Created by Johny Georges on 2024-01-23.
//

#include "ast-symbol-node.h"

ASTSymbolNode::ASTSymbolNode(Symbol* symbol) {
    _symbol = symbol;
}

Symbol* ASTSymbolNode::getSymbol() {
    return _symbol;
}

ASTNodeType ASTSymbolNode::getNodeType() {
    return AST_SYMBOL_NODE;
}