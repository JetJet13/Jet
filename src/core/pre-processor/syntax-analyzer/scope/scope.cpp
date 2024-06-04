//
// Created by Johny Georges on 2024-06-03.
//

#include "scope.h"

Scope::Scope(ASTBlockStartNode* blockStartNode) {
    _blockStartNode = blockStartNode;
    _block = std::vector<ASTNode*>();
}

void Scope::add(ASTNode* node) {
    _block.push_back(node);
}

std::vector<ASTNode*> Scope::getBlock() {
    return _block;
}

ASTBlockNode* Scope::convertToBlockNode(ASTBlockEndNode* blockEndNode) {
    return new ASTBlockNode(_blockStartNode, _block, blockEndNode);
}