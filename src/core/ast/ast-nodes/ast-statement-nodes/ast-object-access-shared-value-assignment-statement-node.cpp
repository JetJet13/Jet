//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-object-access-shared-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessSharedValueAssignmentStatementNode::ASTObjectAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTObjectAccessSharedValueAssignmentNode> objectAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _objectAccessAssignment = objectAccessAssignment;
    _expression = expression;
    _children.push_back(_objectAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTObjectAccessSharedValueAssignmentNode> ASTObjectAccessSharedValueAssignmentStatementNode::getObjectAccessAssignment() {
    return _objectAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTObjectAccessSharedValueAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTObjectAccessSharedValueAssignmentStatementNode::getStartPosition() {
    return _objectAccessAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTObjectAccessSharedValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTObjectAccessSharedValueAssignmentStatementNode::getNodeType() {
    return AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTObjectAccessSharedValueAssignmentStatementNode::toString() {
    return "OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTObjectAccessSharedValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessSharedValueAssignmentStatementNode>(other);
    return this->getObjectAccessAssignment()->isSameAs(otherNode->getObjectAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTObjectAccessSharedValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTObjectAccessSharedValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}