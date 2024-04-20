//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-period-node.h"
#include "ast-class-nodes/ast-this-access-node.h"

ASTNode* ASTPeriodNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_THIS_NODE)) {
        return new ASTThisAccessNode(_lexeme);
    }
    return this;
}

ASTNodeType ASTPeriodNode::getNodeType() {
    return AST_PERIOD_NODE;
}

std::string ASTPeriodNode::toString() {
    return "PERIOD";
}
