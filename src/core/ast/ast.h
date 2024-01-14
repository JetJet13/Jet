//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_H
#define JETLANG_AST_H

#include <vector>
#include "../lexeme/lexeme.h"
#include "ast-nodes/ast-node.h"

class AST {
private:
    std::vector<ASTNode> _children;
public:
    AST();
    void addChild(ASTNode node);
    std::vector<ASTNode> getChildren();
};

#endif //JETLANG_AST_H
