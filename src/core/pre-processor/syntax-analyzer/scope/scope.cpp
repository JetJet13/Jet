//
// Created by Johny Georges on 2024-06-03.
//

#include "scope.h"

Scope::Scope(std::shared_ptr<ASTBlockStartNode> blockStartNode) {
    _blockStartNode = blockStartNode;
    _block = std::vector<std::shared_ptr<ASTNode>>();
}

void Scope::add(std::shared_ptr<ASTNode> node) {
    _block.push_back(node);
}

std::vector<std::shared_ptr<ASTNode>> Scope::getBlock() {
    return _block;
}

std::shared_ptr<ASTBlockNode> Scope::convertToBlockNode(std::shared_ptr<ASTBlockEndNode> blockEndNode) {
    return std::make_shared<ASTBlockNode>(_blockStartNode, _block, blockEndNode);
}

std::stack<std::shared_ptr<ASTNode>> Scope::convertToStack() {
    auto nodeStack = std::stack<std::shared_ptr<ASTNode>>();
    nodeStack.push(_blockStartNode);
    for (auto node : _block) {
        nodeStack.push(node);
    }
    return nodeStack;
}