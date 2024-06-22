//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-colon-node.h"
#include "../ast-type-nodes/ast-type-colon-node.h"
#include "../ast-struct-nodes/ast-struct-colon-node.h"

ASTNode* ASTColonBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE ||
        mode == SA_GROUP_MODE ||
        (prevNode && prevNode.value()->isOneOf({ AST_VARIABLE_DEFINITION_NODE, AST_CLASS_PROPERTY_DEFINITION_NODE }))) {
        return new ASTTypeColonNode(_lexeme);
    }

    if (mode == SA_STRUCT_MODE) {
        return new ASTStructColonNode(_lexeme);
    }
    return this;
}

ASTNodeType ASTColonBaseNode::getNodeType() {
    return AST_COLON_BASE_NODE;
}

std::string ASTColonBaseNode::toString() {
    return "COLON_BASE";
}