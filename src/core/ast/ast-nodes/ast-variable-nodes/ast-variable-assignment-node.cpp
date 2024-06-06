//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-variable-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableAssignmentNode::ASTVariableAssignmentNode(ASTIdentifierNode* astIdentifierNode, ASTAssignmentOperatorNode* assignmentOperator) {
    _identifier = astIdentifierNode;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_identifier);
    _children.push_back(_assignmentOperator);
}

ASTIdentifierNode* ASTVariableAssignmentNode::getIdentifierNode() {
    return _identifier;
}

void ASTVariableAssignmentNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTVariableAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTVariableAssignmentNode::getStartPosition() {
    return _identifier->getStartPosition();
}

Position* ASTVariableAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTVariableAssignmentNode::getNodeType() {
    return AST_VARIABLE_ASSIGNMENT_NODE;
}

std::string ASTVariableAssignmentNode::toString() {
    return "VARIABLE_ASSIGNMENT";
}

bool ASTVariableAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableAssignmentNode*)other;
    return this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTVariableAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTVariableAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_identifier)
    ->addWithWhitespace(_assignmentOperator);
    return sourceCodeBuilder.build();
}