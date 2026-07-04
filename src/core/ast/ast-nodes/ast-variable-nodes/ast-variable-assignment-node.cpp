//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-variable-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableAssignmentNode::ASTVariableAssignmentNode(std::shared_ptr<ASTIdentifierNode> astIdentifierNode, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator) {
    _identifier = astIdentifierNode;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_identifier);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTIdentifierNode> ASTVariableAssignmentNode::getIdentifierNode() {
    return _identifier;
}

void ASTVariableAssignmentNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTVariableAssignmentNode::getTypeSignature() {
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

bool ASTVariableAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTVariableAssignmentNode>(other);
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
    ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}