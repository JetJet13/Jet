//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-condition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTControlFlowConditionNode::ASTControlFlowConditionNode(std::shared_ptr<ASTExpressionNode> condition) {
    _condition = condition;
    _children.push_back(_condition);
}

std::shared_ptr<ASTExpressionNode> ASTControlFlowConditionNode::getCondition() {
    return _condition;
}

void ASTControlFlowConditionNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTControlFlowConditionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTControlFlowConditionNode::getStartPosition() {
    return _condition->getStartPosition();
}

std::shared_ptr<Position> ASTControlFlowConditionNode::getEndPosition() {
    return _condition->getEndPosition();
}

ASTNodeType ASTControlFlowConditionNode::getNodeType() {
    return AST_CONTROL_FLOW_CONDITION_NODE;
}

std::string ASTControlFlowConditionNode::toString() {
    return "CONTROL_FLOW_CONDITION";
}

bool ASTControlFlowConditionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTControlFlowConditionNode>(other);
    return this->getCondition()->isSameAs(otherNode->getCondition());
}

void ASTControlFlowConditionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _condition->print();
    Logger::log("----------");
}

std::string ASTControlFlowConditionNode::toSourceCode() {
    return _condition->toSourceCode();
}