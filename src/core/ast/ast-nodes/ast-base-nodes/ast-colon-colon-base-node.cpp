//
// Created by Johny Georges on 2026-05-30.
//

#include "ast-colon-colon-base-node.h"
#include "../ast-type-nodes/ast-module-type-nodes/ast-module-access-type-node.h"
#include "../ast-module-nodes/ast-module-access-node.h"

std::shared_ptr<ASTNode> ASTColonColonBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_MODULE_TYPE_SOURCE_NODE)) {
        return std::make_shared<ASTModuleAccessTypeNode>(_lexeme);
    }

    return std::make_shared<ASTModuleAccessNode>(_lexeme);
}

ASTNodeType ASTColonColonBaseNode::getNodeType() {
    return AST_COLON_COLON_BASE_NODE;
}

std::string ASTColonColonBaseNode::toString() {
    return "COLON_COLON_BASE";
}