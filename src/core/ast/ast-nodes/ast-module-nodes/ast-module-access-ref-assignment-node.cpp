//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-module-access-ref-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessRefAssignmentNode::ASTModuleAccessRefAssignmentNode(ASTModuleAccessExpressionNode* moduleAccessExpression, ASTRefValueAssignmentOperatorNode* assignmentOperator) {
    _moduleAccessExpression = moduleAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_moduleAccessExpression);
    _children.push_back(_assignmentOperator);
}

ASTModuleAccessExpressionNode* ASTModuleAccessRefAssignmentNode::getModuleAccess() {
    return _moduleAccessExpression;
}

TypeSignature* ASTModuleAccessRefAssignmentNode::getTypeSignature() {
    return _moduleAccessExpression->getTypeSignature();
}

Position* ASTModuleAccessRefAssignmentNode::getStartPosition() {
    return _moduleAccessExpression->getStartPosition();
}

Position* ASTModuleAccessRefAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTModuleAccessRefAssignmentNode::getNodeType() {
    return AST_MODULE_ACCESS_REF_ASSIGNMENT_NODE;
}

std::string ASTModuleAccessRefAssignmentNode::toString() {
    return "MODULE_ACCESS_REF_ASSIGNMENT";
}

bool ASTModuleAccessRefAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleAccessRefAssignmentNode*)other;
    return this->getModuleAccess()->isSameAs(otherNode->getModuleAccess());
}

void ASTModuleAccessRefAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleAccessExpression->print();
    Logger::log("----------");
}

std::string ASTModuleAccessRefAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}