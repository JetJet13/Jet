//
// Created by Johny Georges on 2024-10-24.
//

#include "ast-export-node.h"

ASTNodeType ASTExportNode::getNodeType() {
    return AST_EXPORT_NODE;
}

std::string ASTExportNode::toString() {
    return "EXPORT";
}