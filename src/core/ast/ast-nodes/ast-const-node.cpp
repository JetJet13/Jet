//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-const-node.h"
#include "ast-variable-nodes/ast-variable-type-node.h"

std::shared_ptr<ASTNode> ASTConstNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_STATIC_NODE, AST_PUBLIC_NODE, AST_PROTECTED_NODE, AST_PRIVATE_NODE })) {
        return shared_from_this();
    }
    return std::make_shared<ASTVariableTypeNode>(_lexeme);
}

ASTNodeType ASTConstNode::getNodeType() {
    return AST_CONST_NODE;
}

std::string ASTConstNode::toString() {
    return "CONST";
}