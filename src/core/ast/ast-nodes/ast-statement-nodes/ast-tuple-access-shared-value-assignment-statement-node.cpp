//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-tuple-access-shared-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessSharedValueAssignmentStatementNode::ASTTupleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTTupleAccessSharedValueAssignmentNode> tupleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _tupleAccessAssignment = tupleAccessAssignment;
    _expression = expression;
    _children.push_back(_tupleAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTTupleAccessSharedValueAssignmentNode> ASTTupleAccessSharedValueAssignmentStatementNode::getTupleAccessAssignment() {
    return _tupleAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTTupleAccessSharedValueAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTTupleAccessSharedValueAssignmentStatementNode::getStartPosition() {
    return _tupleAccessAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTTupleAccessSharedValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTTupleAccessSharedValueAssignmentStatementNode::getNodeType() {
    return AST_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTTupleAccessSharedValueAssignmentStatementNode::toString() {
    return "TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTTupleAccessSharedValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessSharedValueAssignmentStatementNode>(other);
    return this->getTupleAccessAssignment()->isSameAs(otherNode->getTupleAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTTupleAccessSharedValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTTupleAccessSharedValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}