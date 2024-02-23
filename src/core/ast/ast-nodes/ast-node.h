//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_NODE_H
#define JETLANG_AST_NODE_H

#include "../../lexeme/lexeme.h"
#include "../types/ast-node-type.h"

class ASTNode {
protected:
    std::optional<ASTNode*> _parentNode;
    ASTNodeType _nodeType;
public:
    void setParentNode(ASTNode* parentNode);
    virtual ASTNodeType getNodeType() = 0;
    bool is(ASTNodeType astNodeType);
};
#endif //JETLANG_AST_NODE_H
