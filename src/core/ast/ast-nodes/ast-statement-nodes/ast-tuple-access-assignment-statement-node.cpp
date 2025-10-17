//
// Created by Johny Georges on 2025-10-16.
//

#include "ast-tuple-access-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessAssignmentStatementNode::ASTTupleAccessAssignmentStatementNode(ASTTupleAccessAssignmentNode* tupleAccessAssignment, ASTExpressionNode* expression) {
    _tupleAccessAssignment = tupleAccessAssignment;
    _expression = expression;
    _children.push_back(_tupleAccessAssignment);
    _children.push_back(_expression);
}

ASTTupleAccessAssignmentNode* ASTTupleAccessAssignmentStatementNode::getTupleAccessAssignment() {
    return _tupleAccessAssignment;
}

ASTExpressionNode* ASTTupleAccessAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTTupleAccessAssignmentStatementNode::getStartPosition() {
    return _tupleAccessAssignment->getStartPosition();
}

Position* ASTTupleAccessAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTTupleAccessAssignmentStatementNode::getNodeType() {
    return AST_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTTupleAccessAssignmentStatementNode::toString() {
    return "TUPLE_ACCESS_ASSIGNMENT_STATEMENT";
}

bool ASTTupleAccessAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleAccessAssignmentStatementNode*)other;
    return this->getTupleAccessAssignment()->isSameAs(otherNode->getTupleAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTTupleAccessAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTTupleAccessAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}