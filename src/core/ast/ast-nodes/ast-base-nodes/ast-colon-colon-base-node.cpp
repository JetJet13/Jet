//
// Created by Johny Georges on 2026-05-30.
//

#include "ast-colon-colon-base-node.h"
#include "../ast-type-nodes/ast-module-type-nodes/ast-module-access-type-node.h"
#include "../ast-module-nodes/ast-module-access-node.h"

ASTNode* ASTColonColonBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_MODULE_TYPE_SOURCE_NODE)) {
        return new ASTModuleAccessTypeNode(_lexeme);
    }

    return new ASTModuleAccessNode(_lexeme);
}

ASTNodeType ASTColonColonBaseNode::getNodeType() {
    return AST_COLON_COLON_BASE_NODE;
}

std::string ASTColonColonBaseNode::toString() {
    return "COLON_COLON_BASE";
}