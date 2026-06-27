//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-array-access-ref-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessRefAssignmentNode::ASTArrayAccessRefAssignmentNode(ASTArrayAccessExpressionNode* arrayAccessExpression, ASTRefValueAssignmentOperatorNode* assignmentOperator) {
    _arrayAccessExpression = arrayAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_arrayAccessExpression);
    _children.push_back(_assignmentOperator);
}

ASTArrayAccessExpressionNode* ASTArrayAccessRefAssignmentNode::getArrayAccess() {
    return _arrayAccessExpression;
}

TypeSignature* ASTArrayAccessRefAssignmentNode::getTypeSignature() {
    return _arrayAccessExpression->getTypeSignature();
}

Position* ASTArrayAccessRefAssignmentNode::getStartPosition() {
    return _arrayAccessExpression->getStartPosition();
}

Position* ASTArrayAccessRefAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTArrayAccessRefAssignmentNode::getNodeType() {
    return AST_ARRAY_ACCESS_REF_ASSIGNMENT_NODE;
}

std::string ASTArrayAccessRefAssignmentNode::toString() {
    return "ARRAY_ACCESS_REF_ASSIGNMENT";
}

bool ASTArrayAccessRefAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTArrayAccessRefAssignmentNode*)other;
    return this->getArrayAccess()->isSameAs(otherNode->getArrayAccess());
}

void ASTArrayAccessRefAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccessExpression->print();
    Logger::log("----------");
}

std::string ASTArrayAccessRefAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}