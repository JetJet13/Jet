//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-tuple-access-ref-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessRefAssignmentStatementNode::ASTTupleAccessRefAssignmentStatementNode(ASTTupleAccessRefAssignmentNode* tupleAccessAssignment, ASTExpressionNode* expression) {
    _tupleAccessAssignment = tupleAccessAssignment;
    _expression = expression;
    _children.push_back(_tupleAccessAssignment);
    _children.push_back(_expression);
}

ASTTupleAccessRefAssignmentNode* ASTTupleAccessRefAssignmentStatementNode::getTupleAccessAssignment() {
    return _tupleAccessAssignment;
}

ASTExpressionNode* ASTTupleAccessRefAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTTupleAccessRefAssignmentStatementNode::getStartPosition() {
    return _tupleAccessAssignment->getStartPosition();
}

Position* ASTTupleAccessRefAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTTupleAccessRefAssignmentStatementNode::getNodeType() {
    return AST_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTTupleAccessRefAssignmentStatementNode::toString() {
    return "TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT";
}

bool ASTTupleAccessRefAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleAccessRefAssignmentStatementNode*)other;
    return this->getTupleAccessAssignment()->isSameAs(otherNode->getTupleAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTTupleAccessRefAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTTupleAccessRefAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}