//
// Created by Johny Georges on 2024-03-25.
//

#include "function-argument-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-node.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"

ASTNode* FunctionArgumentListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto functionArgumentListNode = new ASTFunctionArgumentListNode((ASTFunctionArgumentListStartNode*)nodes[0], (ASTFunctionArgumentListEndNode*)nodes[nodes.size() - 1]);
    for (auto node : nodes) {
        if (node->is(AST_FUNCTION_ARGUMENT_NODE)) {
            functionArgumentListNode->addArgument((ASTFunctionArgumentNode*)node);
        }
    }
    return functionArgumentListNode;
}