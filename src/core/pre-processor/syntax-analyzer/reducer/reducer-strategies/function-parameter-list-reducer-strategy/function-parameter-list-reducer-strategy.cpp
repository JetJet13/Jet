//
// Created by Johny Georges on 2024-03-19.
//

#include "function-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"

ASTNode* FunctionParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto functionParameterListNode = new ASTFunctionParameterListNode(
            (ASTFunctionParameterListStartNode*)nodes[0],
            (ASTFunctionParameterListEndNode*)nodes[nodes.size() - 1]
    );
    for (auto node : nodes) {
        if (node->is(AST_FUNCTION_PARAMETER_NODE)) {
            functionParameterListNode->addParameter((ASTFunctionParameterNode*)node);
        }

        if (node->is(AST_COMMA_NODE)) {
            functionParameterListNode->addComma((ASTCommaNode*)node);
        }
    }
    return functionParameterListNode;
}