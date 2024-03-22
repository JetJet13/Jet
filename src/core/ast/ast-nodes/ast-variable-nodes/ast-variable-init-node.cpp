//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-init-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTVariableInitNode::ASTVariableInitNode(ASTVariableTypeNode* assignmentTypeQualifier, ASTIdentifierNode* astIdentifierNode) {
    _assignmentTypeQualifier = assignmentTypeQualifier;
    _identifier = astIdentifierNode;
}

ASTVariableTypeNode* ASTVariableInitNode::getVarTypeNode() {
    return _assignmentTypeQualifier;
}

ASTIdentifierNode* ASTVariableInitNode::getIdentifierNode() {
    return _identifier;
}

ASTNodeType ASTVariableInitNode::getNodeType() {
    return AST_VARIABLE_INIT_NODE;
}

std::string ASTVariableInitNode::toString() {
    return "VARIABLE_INIT";
}

bool ASTVariableInitNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableInitNode*)other;
    return this->getVarTypeNode()->isSameAs(otherNode->getVarTypeNode()) &&
           this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTVariableInitNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _assignmentTypeQualifier->print();
    _identifier->print();
    Logger::log("----------");
}