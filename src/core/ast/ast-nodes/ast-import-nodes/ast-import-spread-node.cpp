//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-spread-node.h"

ASTNodeType ASTImportSpreadNode::getNodeType() {
    return AST_IMPORT_SPREAD_NODE;
}

std::string ASTImportSpreadNode::toString() {
    return "IMPORT_SPREAD";
}