//
// Created by Johny Georges on 2025-08-27.
//

#include "ast-object-access-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessAssignmentNode::ASTObjectAccessAssignmentNode(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator) {
    _objectAccessExpression = objectAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_objectAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTObjectAccessExpressionNode> ASTObjectAccessAssignmentNode::getObjectAccess() {
    return _objectAccessExpression;
}

std::shared_ptr<TypeSignature> ASTObjectAccessAssignmentNode::getTypeSignature() {
    return _objectAccessExpression->getTypeSignature();
}

std::shared_ptr<Position> ASTObjectAccessAssignmentNode::getStartPosition() {
    return _objectAccessExpression->getStartPosition();
}

std::shared_ptr<Position> ASTObjectAccessAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTObjectAccessAssignmentNode::getNodeType() {
    return AST_OBJECT_ACCESS_ASSIGNMENT_NODE;
}

std::string ASTObjectAccessAssignmentNode::toString() {
    return "OBJECT_ACCESS_ASSIGNMENT";
}

bool ASTObjectAccessAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessAssignmentNode>(other);
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