//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-object-access-ref-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessRefAssignmentStatementNode::ASTObjectAccessRefAssignmentStatementNode(ASTObjectAccessRefAssignmentNode* objectAccessAssignment, ASTExpressionNode* expression) {
    _objectAccessAssignment = objectAccessAssignment;
    _expression = expression;
    _children.push_back(_objectAccessAssignment);
    _children.push_back(_expression);
}

ASTObjectAccessRefAssignmentNode* ASTObjectAccessRefAssignmentStatementNode::getObjectAccessAssignment() {
    return _objectAccessAssignment;
}

ASTExpressionNode* ASTObjectAccessRefAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTObjectAccessRefAssignmentStatementNode::getStartPosition() {
    return _objectAccessAssignment->getStartPosition();
}

Position* ASTObjectAccessRefAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTObjectAccessRefAssignmentStatementNode::getNodeType() {
    return AST_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTObjectAccessRefAssignmentStatementNode::toString() {
    return "OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT";
}

bool ASTObjectAccessRefAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessRefAssignmentStatementNode*)other;
    return this->getObjectAccessAssignment()->isSameAs(otherNode->getObjectAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTObjectAccessRefAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTObjectAccessRefAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}