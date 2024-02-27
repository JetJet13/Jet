//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-slash-operator-node.h"


ASTNodeType ASTSlashOperatorNode::getNodeType() {
    return AST_SLASH_OPERATOR_NODE;
}

std::string ASTSlashOperatorNode::toString() {
    return "SLASH_OPERATOR";
}
