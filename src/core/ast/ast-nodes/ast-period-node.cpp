//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-period-node.h"
#include "ast-class-nodes/ast-this-access-node.h"

std::shared_ptr<ASTNode> ASTPeriodNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_THIS_NODE)) {
        return std::make_shared<ASTThisAccessNode>(_lexeme);
    }
    return shared_from_this();
}

ASTNodeType ASTPeriodNode::getNodeType() {
    return AST_PERIOD_NODE;
}

std::string ASTPeriodNode::toString() {
    return "PERIOD";
}
