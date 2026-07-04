//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-tuple-access-ref-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessRefAssignmentStatementNode::ASTTupleAccessRefAssignmentStatementNode(std::shared_ptr<ASTTupleAccessRefAssignmentNode> tupleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _tupleAccessAssignment = tupleAccessAssignment;
    _expression = expression;
    _children.push_back(_tupleAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTTupleAccessRefAssignmentNode> ASTTupleAccessRefAssignmentStatementNode::getTupleAccessAssignment() {
    return _tupleAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTTupleAccessRefAssignmentStatementNode::getExpression() {
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

bool ASTTupleAccessRefAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessRefAssignmentStatementNode>(other);
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