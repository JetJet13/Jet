//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-module-access-ref-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessRefAssignmentStatementNode::ASTModuleAccessRefAssignmentStatementNode(ASTModuleAccessRefAssignmentNode* moduleAccessAssignment, ASTExpressionNode* expression) {
    _moduleAccessAssignment = moduleAccessAssignment;
    _expression = expression;
    _children.push_back(_moduleAccessAssignment);
    _children.push_back(_expression);
}

ASTModuleAccessRefAssignmentNode* ASTModuleAccessRefAssignmentStatementNode::getModuleAccessAssignment() {
    return _moduleAccessAssignment;
}

ASTExpressionNode* ASTModuleAccessRefAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTModuleAccessRefAssignmentStatementNode::getStartPosition() {
    return _moduleAccessAssignment->getStartPosition();
}

Position* ASTModuleAccessRefAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTModuleAccessRefAssignmentStatementNode::getNodeType() {
    return AST_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTModuleAccessRefAssignmentStatementNode::toString() {
    return "MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT";
}

bool ASTModuleAccessRefAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleAccessRefAssignmentStatementNode*)other;
    return this->getModuleAccessAssignment()->isSameAs(otherNode->getModuleAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTModuleAccessRefAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTModuleAccessRefAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}