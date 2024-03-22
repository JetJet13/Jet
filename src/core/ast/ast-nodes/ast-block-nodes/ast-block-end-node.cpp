//
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-end-node.h"
#include "../ast-struct-nodes/ast-struct-end-node.h"

ASTBlockEndNode::ASTBlockEndNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode* ASTBlockEndNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
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