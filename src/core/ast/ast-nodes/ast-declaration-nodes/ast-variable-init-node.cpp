//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-init-node.h"

ASTVariableInitNode::ASTVariableInitNode(ASTVariableTypeNode* assignmentTypeQualifier, ASTIdentifierNode* astIdentifierNode) {
    _assignmentTypeQualifier = assignmentTypeQualifier;
    _identifier = astIdentifierNode;
}

void ASTVariableInitNode::setIdentifier(ASTIdentifierNode* astIdentifierNode) {
    _identifier = astIdentifierNode;
}

ASTNodeType ASTVariableInitNode::getNodeType() {
    return AST_VARIABLE_INIT_NODE;
}

std::string ASTVariableInitNode::toString() {
    return "VARIABLE_INIT";
}