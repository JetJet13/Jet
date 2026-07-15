//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-array-access-shared-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessSharedValueAssignmentStatementNode::ASTArrayAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTArrayAccessSharedValueAssignmentNode> arrayAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _arrayAccessAssignment = arrayAccessAssignment;
    _expression = expression;
    _children.push_back(_arrayAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTArrayAccessSharedValueAssignmentNode> ASTArrayAccessSharedValueAssignmentStatementNode::getArrayAccessAssignment() {
    return _arrayAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTArrayAccessSharedValueAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTArrayAccessSharedValueAssignmentStatementNode::getStartPosition() {
    return _arrayAccessAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTArrayAccessSharedValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTArrayAccessSharedValueAssignmentStatementNode::getNodeType() {
    return AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTArrayAccessSharedValueAssignmentStatementNode::toString() {
    return "ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTArrayAccessSharedValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessSharedValueAssignmentStatementNode>(other);
    return this->getArrayAccessAssignment()->isSameAs(otherNode->getArrayAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTArrayAccessSharedValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTArrayAccessSharedValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}