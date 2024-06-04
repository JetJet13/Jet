//
// Created by Johny Georges on 2024-06-03.
//

#ifndef JETLANG_SCOPE_H
#define JETLANG_SCOPE_H

#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-start-node.h"
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"

class Scope {
private:
    ASTBlockStartNode* _blockStartNode;
    std::vector<ASTNode*> _block;
public:
    Scope(ASTBlockStartNode* blockStartNode);
    void add(ASTNode* node);
    std::vector<ASTNode*> getBlock();
    ASTBlockNode* convertToBlockNode(ASTBlockEndNode* blockEndNode);
};

#endif //JETLANG_SCOPE_H
