//
// Created by Johny Georges on 2024-04-15.
//

#include "ast-import-wildcard-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTImportWildcardNode::getNodeType() {
    return AST_IMPORT_WILDCARD_NODE;
}

std::string ASTImportWildcardNode::toString() {
    return "IMPORT_WILDCARD";
}