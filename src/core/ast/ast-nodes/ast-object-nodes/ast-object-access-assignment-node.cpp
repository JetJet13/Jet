//
// Created by Johny Georges on 2025-08-27.
//

#include "ast-object-access-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessAssignmentNode::ASTObjectAccessAssignmentNode(ASTObjectAccessExpressionNode* objectAccessExpression, ASTAssignmentOperatorNode* assignmentOperator) {
    _objectAccessExpression = objectAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_objectAccessExpression);
    _children.push_back(_assignmentOperator);
}

ASTObjectAccessExpressionNode* ASTObjectAccessAssignmentNode::getObjectAccess() {
    return _objectAccessExpression;
}

TypeSignature* ASTObjectAccessAssignmentNode::getTypeSignature() {
    return _objectAccessExpression->getTypeSignature();
}

Position* ASTObjectAccessAssignmentNode::getStartPosition() {
    return _objectAccessExpression->getStartPosition();
}

Position* ASTObjectAccessAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTObjectAccessAssignmentNode::getNodeType() {
    return AST_OBJECT_ACCESS_ASSIGNMENT_NODE;
}

std::string ASTObjectAccessAssignmentNode::toString() {
    return "OBJECT_ACCESS_ASSIGNMENT";
}

bool ASTObjectAccessAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessAssignmentNode*)other;
    return this->getObjectAccess()->isSameAs(otherNode->getObjectAccess());
}

void ASTObjectAccessAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccessExpression->print();
    Logger::log("----------");
}

std::string ASTObjectAccessAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccessExpression)
    ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}