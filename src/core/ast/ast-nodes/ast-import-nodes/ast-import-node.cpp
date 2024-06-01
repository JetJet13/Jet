//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTImportNode::getNodeType() {
    return AST_IMPORT_NODE;
}

std::string ASTImportNode::toString() {
    return "IMPORT";
}
