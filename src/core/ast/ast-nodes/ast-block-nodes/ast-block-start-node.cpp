//
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-start-node.h"
#include "../ast-struct-nodes/ast-struct-start-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-start-node.h"

ASTBlockStartNode::ASTBlockStartNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode* ASTBlockStartNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_VARIABLE_INIT_NODE, AST_COLON_NODE, AST_LEFT_BRACKET_NODE })) {
        return new ASTStructStartNode(_lexeme);
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_ENUM_NAME_NODE })) {
        return new ASTEnumKeyValueListStartNode(_lexeme);
    }
    return this;
}

ASTNodeType ASTBlockStartNode::getNodeType() {
    return AST_BLOCK_START_NODE;
}

std::string ASTBlockStartNode::toString() {
    return "BLOCK_START";
}