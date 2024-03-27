//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-object-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessExpressionNode::ASTObjectAccessExpressionNode(ASTObjectAccessSourceNode* source, ASTObjectAccessTargetNode* property) {
    _source = source;
    _target = property;
}

ASTObjectAccessSourceNode* ASTObjectAccessExpressionNode::getSource() {
    return _source;
}

ASTObjectAccessTargetNode* ASTObjectAccessExpressionNode::getTarget() {
    return _target;
}

ASTNodeType ASTObjectAccessExpressionNode::getNodeType() {
    return AST_OBJECT_ACCESS_EXPRESSION_NODE;
}

std::string ASTObjectAccessExpressionNode::toString() {
    return "OBJECT_ACCESS_EXPRESSION";
}

bool ASTObjectAccessExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessExpressionNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource()) &&
            this->getTarget()->isSameAs(otherNode->getTarget());
}

void ASTObjectAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _target->print();
    Logger::log("----------");
}