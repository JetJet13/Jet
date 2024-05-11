//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-catch-block-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTCatchBlockNode::ASTCatchBlockNode(ASTControlFlowBlockNode* block, std::optional<ASTCatchErrorVariableNode*> errorVariable) {
    _block = block;
    _errorVariable = errorVariable;
    _children.push_back(_block);
    if (_errorVariable) {
        _children.push_back(_errorVariable.value());
    }
}

ASTControlFlowBlockNode* ASTCatchBlockNode::getBlock() {
    return _block;
}

std::optional<ASTCatchErrorVariableNode*> ASTCatchBlockNode::getErrorVariable() {
    return _errorVariable;
}

ASTNodeType ASTCatchBlockNode::getNodeType() {
    return AST_CATCH_BLOCK_NODE;
}

std::string ASTCatchBlockNode::toString() {
    return "CATCH_BLOCK";
}

bool ASTCatchBlockNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTCatchBlockNode*)other;

    if (!_errorVariable.has_value() && otherNode->getErrorVariable().has_value() ||
        _errorVariable.has_value() && !otherNode->getErrorVariable().has_value()) {
        return false;
    }

    if (_errorVariable.has_value() && otherNode->getErrorVariable().has_value() &&
        !_errorVariable.value()->isSameAs(otherNode->getErrorVariable().value())) {
        return false;
    }

    return this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTCatchBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_errorVariable) {
        _errorVariable.value()->print();
    }
    _block->print();
    Logger::log("----------");
}