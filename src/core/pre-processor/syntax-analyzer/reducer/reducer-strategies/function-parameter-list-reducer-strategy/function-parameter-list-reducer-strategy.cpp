//
// Created by Johny Georges on 2024-03-19.
//

#include "function-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"

ASTNode* FunctionParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto functionParameterListNode = new ASTFunctionParameterListNode();
    for (auto node : nodes) {
        if (node->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
            functionParameterListNode->addParameter((ASTIdentifierExpressionNode*)node);
        }
    }
    return functionParameterListNode;
}