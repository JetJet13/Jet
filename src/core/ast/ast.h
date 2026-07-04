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
    std::vector<std::shared_ptr<ASTNode>> _children;
public:
    AST();
    void addChild(std::shared_ptr<ASTNode> node);
    std::vector<std::shared_ptr<ASTNode>> getChildren();
};

#endif //JETLANG_AST_H
