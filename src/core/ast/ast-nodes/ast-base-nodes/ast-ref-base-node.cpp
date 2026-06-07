//
// Created by Johny Georges on 2025-01-15.
//

#include "ast-ref-base-node.h"
#include "../ast-ref-node.h"
#include "../ast-type-nodes/ast-ref-type-keyword-node.h"

ASTNode* ASTRefBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE || mode == SA_TYPE_PARAMETER_LIST_MODE || mode == SA_LAMBDA_TYPE_PARAMETER_LIST_MODE ||
        (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_PARAMETER_LIST_NODE, AST_PROCEDURE_PARAMETER_LIST_NODE, AST_TYPE_COLON_NODE, AST_TYPE_ASSIGNMENT_OPERATOR_NODE, AST_INTERFACE_COLON_NODE }))) {
        return new ASTRefTypeKeywordNode(_lexeme);
    }

    return new ASTRefNode(_lexeme);
}

ASTNodeType ASTRefBaseNode::getNodeType() {
    return AST_REF_BASE_NODE;
}

std::string ASTRefBaseNode::toString() {
    return "REF_BASE";
}