//
// Created by Johny Georges on 2026-04-02.
//

#include "ast-module-access-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessAssignmentNode::ASTModuleAccessAssignmentNode(ASTModuleAccessExpressionNode* moduleAccessExpression, ASTAssignmentOperatorNode* assignmentOperator) {
    _moduleAccessExpression = moduleAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_moduleAccessExpression);
    _children.push_back(_assignmentOperator);
}

ASTModuleAccessExpressionNode* ASTModuleAccessAssignmentNode::getModuleAccess() {
    return _moduleAccessExpression;
}

TypeSignature* ASTModuleAccessAssignmentNode::getTypeSignature() {
    return _moduleAccessExpression->getTypeSignature();
}

Position* ASTModuleAccessAssignmentNode::getStartPosition() {
    return _moduleAccessExpression->getStartPosition();
}

Position* ASTModuleAccessAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTModuleAccessAssignmentNode::getNodeType() {
    return AST_MODULE_ACCESS_ASSIGNMENT_NODE;
}

std::string ASTModuleAccessAssignmentNode::toString() {
    return "MODULE_ACCESS_ASSIGNMENT";
}

bool ASTModuleAccessAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleAccessAssignmentNode*)other;
    return this->getModuleAccess()->isSameAs(otherNode->getModuleAccess());
}

void ASTModuleAccessAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleAccessExpression->print();
    Logger::log("----------");
}

std::string ASTModuleAccessAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleAccessExpression)
    ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}