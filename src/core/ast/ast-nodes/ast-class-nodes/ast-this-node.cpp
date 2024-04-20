//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-this-node.h"
#include "../ast-type-nodes/ast-type-node-factory.h"
#include "../ast-expression-nodes/ast-this-expression-node.h"

ASTNode* ASTThisNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_PARAMETER_LIST_NODE })) {
        return ASTTypeNodeFactory::createThisTypeNode(this);
    }

    return this;
}

ASTNodeType ASTThisNode::getNodeType() {
    return AST_THIS_NODE;
}

std::string ASTThisNode::toString() {
    return "THIS";
}