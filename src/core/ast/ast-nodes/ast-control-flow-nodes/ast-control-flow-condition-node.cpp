//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-condition-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTControlFlowConditionNode::ASTControlFlowConditionNode(ASTExpressionNode* condition) {
    _condition = condition;
    _children.push_back(_condition);
}

ASTExpressionNode* ASTControlFlowConditionNode::getCondition() {
    return _condition;
}

void ASTControlFlowConditionNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTControlFlowConditionNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTControlFlowConditionNode::getNodeType() {
    return AST_CONTROL_FLOW_CONDITION_NODE;
}

std::string ASTControlFlowConditionNode::toString() {
    return "CONTROL_FLOW_CONDITION";
}

bool ASTControlFlowConditionNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTControlFlowConditionNode*)other;
    return this->getCondition()->isSameAs(otherNode->getCondition());
}

void ASTControlFlowConditionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _condition->print();
    Logger::log("----------");
}