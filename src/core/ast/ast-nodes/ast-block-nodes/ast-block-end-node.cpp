//
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-end-node.h"
#include "../ast-struct-nodes/ast-struct-end-node.h"

ASTBlockEndNode::ASTBlockEndNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode* ASTBlockEndNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, HandleMode mode) {
    if (nextNode && nextNode.value()->isOneOf({ AST_TERMINATOR_NODE, AST_COMMA_NODE, AST_RIGHT_BRACKET_NODE, AST_BLOCK_END_NODE, AST_STRUCT_END_NODE })) {
        return new ASTStructEndNode(_lexeme);
    }
    return this;
}

ASTNodeType ASTBlockEndNode::getNodeType() {
    return AST_BLOCK_END_NODE;
}

std::string ASTBlockEndNode::toString() {
    return "BLOCK_END";
}