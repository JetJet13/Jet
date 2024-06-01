//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-variable-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableAssignmentStatementNode::ASTVariableAssignmentStatementNode(ASTVariableAssignmentNode* variable, ASTExpressionNode* expression) {
    _variableAssignment = variable;
    _expression = expression;
    _children.push_back(_variableAssignment);
    _children.push_back(_expression);
}

ASTVariableAssignmentNode* ASTVariableAssignmentStatementNode::getVariableAssignment() {
    return _variableAssignment;
}

ASTExpressionNode* ASTVariableAssignmentStatementNode::getExpression() {
    return _expression;
}

ASTNodeType ASTVariableAssignmentStatementNode::getNodeType() {
    return AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTVariableAssignmentStatementNode::toString() {
    return "VARIABLE_ASSIGNMENT_STATEMENT";
}

bool ASTVariableAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableAssignmentStatementNode*)other;
    return this->getVariableAssignment()->isSameAs(otherNode->getVariableAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTVariableAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variableAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTVariableAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_variableAssignment)
    ->addWithWhitespace(_expression);
    return sourceCodeBuilder.build();
}