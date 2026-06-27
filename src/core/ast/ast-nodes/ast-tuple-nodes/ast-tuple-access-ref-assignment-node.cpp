//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-tuple-access-ref-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessRefAssignmentNode::ASTTupleAccessRefAssignmentNode(ASTTupleAccessExpressionNode* tupleAccessExpression, ASTRefValueAssignmentOperatorNode* assignmentOperator) {
    _tupleAccessExpression = tupleAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_tupleAccessExpression);
    _children.push_back(_assignmentOperator);
}

ASTTupleAccessExpressionNode* ASTTupleAccessRefAssignmentNode::getTupleAccess() {
    return _tupleAccessExpression;
}

TypeSignature* ASTTupleAccessRefAssignmentNode::getTypeSignature() {
    return _tupleAccessExpression->getTypeSignature();
}

Position* ASTTupleAccessRefAssignmentNode::getStartPosition() {
    return _tupleAccessExpression->getStartPosition();
}

Position* ASTTupleAccessRefAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTTupleAccessRefAssignmentNode::getNodeType() {
    return AST_TUPLE_ACCESS_REF_ASSIGNMENT_NODE;
}

std::string ASTTupleAccessRefAssignmentNode::toString() {
    return "TUPLE_ACCESS_REF_ASSIGNMENT";
}

bool ASTTupleAccessRefAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleAccessRefAssignmentNode*)other;
    return this->getTupleAccess()->isSameAs(otherNode->getTupleAccess());
}

void ASTTupleAccessRefAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleAccessExpression->print();
    Logger::log("----------");
}

std::string ASTTupleAccessRefAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}