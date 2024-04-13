//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-string-literal-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"

ASTNode * ASTStringLiteralNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {

    if (prevNode && prevNode.value()->is(AST_FROM_NODE)) {
        return new ASTImportPathNode(this);
    }

    return this;
}

ASTNodeType ASTStringLiteralNode::getNodeType() {
    return AST_STRING_LITERAL_NODE;
}

std::string ASTStringLiteralNode::toString() {
    return "STRING_LITERAL - " + _lexemeLiteral->toString();
}
