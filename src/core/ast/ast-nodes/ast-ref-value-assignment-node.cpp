//
// Created by Johny Georges on 2026-02-16.
//

#include "ast-ref-value-assignment-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../types/source-code-builder/source-code-builder.h"

ASTRefValueAssignmentNode::ASTRefValueAssignmentNode(std::shared_ptr<ASTIdentifierNode> astIdentifierNode, std::shared_ptr<ASTRefValueAssignmentOperatorNode> assignmentOperator) {
    _identifier = astIdentifierNode;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_identifier);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTIdentifierNode> ASTRefValueAssignmentNode::getIdentifierNode() {
    return _identifier;
}

void ASTRefValueAssignmentNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTRefValueAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTRefValueAssignmentNode::getStartPosition() {
    return _identifier->getStartPosition();
}

Position* ASTRefValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTRefValueAssignmentNode::getNodeType() {
    return AST_REF_VALUE_ASSIGNMENT_NODE;
}

std::string ASTRefValueAssignmentNode::toString() {
    return "REF_VALUE_ASSIGNMENT";
}

bool ASTRefValueAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTRefValueAssignmentNode>(other);
    return this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTRefValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTRefValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_identifier)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}