//
// Created by Johny Georges on 2024-06-03.
//

#ifndef JETLANG_SCOPE_H
#define JETLANG_SCOPE_H

#include <stack>
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-start-node.h"
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"

class Scope {
private:
    std::shared_ptr<ASTBlockStartNode> _blockStartNode;
    std::vector<std::shared_ptr<ASTNode>> _block;
public:
    Scope(std::shared_ptr<ASTBlockStartNode> blockStartNode);
    void add(std::shared_ptr<ASTNode> node);
    std::vector<std::shared_ptr<ASTNode>> getBlock();
    std::shared_ptr<ASTBlockNode> convertToBlockNode(std::shared_ptr<ASTBlockEndNode> blockEndNode);
    std::stack<std::shared_ptr<ASTNode>> convertToStack();
};

#endif //JETLANG_SCOPE_H
