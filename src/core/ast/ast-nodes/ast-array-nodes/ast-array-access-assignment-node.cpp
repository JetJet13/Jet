//
// Created by Johny Georges on 2025-02-17.
//

#include "ast-array-access-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessAssignmentNode::ASTArrayAccessAssignmentNode(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator) {
    _arrayAccessExpression = arrayAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_arrayAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTArrayAccessExpressionNode> ASTArrayAccessAssignmentNode::getArrayAccess() {
    return _arrayAccessExpression;
}

std::shared_ptr<TypeSignature> ASTArrayAccessAssignmentNode::getTypeSignature() {
    return _arrayAccessExpression->getTypeSignature();
}

std::shared_ptr<Position> ASTArrayAccessAssignmentNode::getStartPosition() {
    return _arrayAccessExpression->getStartPosition();
}

std::shared_ptr<Position> ASTArrayAccessAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTArrayAccessAssignmentNode::getNodeType() {
    return AST_ARRAY_ACCESS_ASSIGNMENT_NODE;
}

std::string ASTArrayAccessAssignmentNode::toString() {
    return "ARRAY_ACCESS_ASSIGNMENT";
}

bool ASTArrayAccessAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessAssignmentNode>(other);
    return this->getArrayAccess()->isSameAs(otherNode->getArrayAccess());
}

void ASTArrayAccessAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccessExpression->print();
    Logger::log("----------");
}

std::string ASTArrayAccessAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}