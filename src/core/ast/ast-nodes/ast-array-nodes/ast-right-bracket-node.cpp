//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-right-bracket-node.h"
#include "../ast-type-nodes/ast-array-type-nodes/ast-array-type-end-node.h"

std::shared_ptr<ASTNode> ASTRightBracketNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_TYPE_PARAMETER_LIST_MODE ||
        (prevNode && prevNode.value()->isOneOf({ AST_TYPE_NODE }))) {
        return std::make_shared<ASTArrayTypeEndNode>(this->getLexeme());
    }
    return shared_from_this();
}

ASTNodeType ASTRightBracketNode::getNodeType() {
    return AST_RIGHT_BRACKET_NODE;
}

std::string ASTRightBracketNode::toString() {
    return "RIGHT_BRACKET";
}