//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_NODE_H
#define JETLANG_AST_NODE_H

#include "../../lexeme/lexeme.h"

class ASTNode {
protected:
    std::optional<ASTNode*> _parentNode;
public:
    void setParentNode(ASTNode* parentNode);
};
#endif //JETLANG_AST_NODE_H
