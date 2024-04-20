//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-const-node.h"
#include "ast-variable-nodes/ast-variable-type-node.h"

ASTNode* ASTConstNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_CLASS_BLOCK_MODE) {
        return this;
    }
    return new ASTVariableTypeNode(_lexeme);
}

ASTNodeType ASTConstNode::getNodeType() {
    return AST_CONST_NODE;
}

std::string ASTConstNode::toString() {
    return "CONST";
}