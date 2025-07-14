//
// Created by Johny Georges on 2025-02-17.
//

#include "ast-array-access-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessAssignmentStatementNode::ASTArrayAccessAssignmentStatementNode(ASTArrayAccessAssignmentNode* arrayAccessAssignment, ASTExpressionNode* expression) {
    _arrayAccessAssignment = arrayAccessAssignment;
    _expression = expression;
    _children.push_back(_arrayAccessAssignment);
    _children.push_back(_expression);
}

ASTArrayAccessAssignmentNode* ASTArrayAccessAssignmentStatementNode::getArrayAccessAssignment() {
    return _arrayAccessAssignment;
}

ASTExpressionNode* ASTArrayAccessAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTArrayAccessAssignmentStatementNode::getStartPosition() {
    return _arrayAccessAssignment->getStartPosition();
}

Position* ASTArrayAccessAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTArrayAccessAssignmentStatementNode::getNodeType() {
    return AST_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTArrayAccessAssignmentStatementNode::toString() {
    return "ARRAY_ACCESS_ASSIGNMENT_STATEMENT";
}

bool ASTArrayAccessAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTArrayAccessAssignmentStatementNode*)other;
    return this->getArrayAccessAssignment()->isSameAs(otherNode->getArrayAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTArrayAccessAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTArrayAccessAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}