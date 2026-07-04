//
// Created by Johny Georges on 2026-06-26.
//

#include "ast-object-access-ref-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessRefAssignmentNode::ASTObjectAccessRefAssignmentNode(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, std::shared_ptr<ASTRefValueAssignmentOperatorNode> assignmentOperator) {
    _objectAccessExpression = objectAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_objectAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTObjectAccessExpressionNode> ASTObjectAccessRefAssignmentNode::getObjectAccess() {
    return _objectAccessExpression;
}

TypeSignature* ASTObjectAccessRefAssignmentNode::getTypeSignature() {
    return _objectAccessExpression->getTypeSignature();
}

Position* ASTObjectAccessRefAssignmentNode::getStartPosition() {
    return _objectAccessExpression->getStartPosition();
}

Position* ASTObjectAccessRefAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTObjectAccessRefAssignmentNode::getNodeType() {
    return AST_OBJECT_ACCESS_REF_ASSIGNMENT_NODE;
}

std::string ASTObjectAccessRefAssignmentNode::toString() {
    return "OBJECT_ACCESS_REF_ASSIGNMENT";
}

bool ASTObjectAccessRefAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessRefAssignmentNode>(other);
    return this->getObjectAccess()->isSameAs(otherNode->getObjectAccess());
}

void ASTObjectAccessRefAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccessExpression->print();
    Logger::log("----------");
}

std::string ASTObjectAccessRefAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}