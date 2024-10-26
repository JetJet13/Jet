//
// Created by Johny Georges on 2024-03-18.
//

#include "function-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"

ASTNode* FunctionDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to function declaration since nodes list is not of size 2 or 3");
    }

    if (nodes.size() == 2) {
        return new ASTFunctionDeclarationNode(
                (ASTFunctionDefinitionNode*)nodes[0],
                (ASTFunctionBlockNode*)nodes[1]
        );
    }

    return new ASTFunctionDeclarationNode(
            (ASTFunctionDefinitionNode*)nodes[1],
            (ASTFunctionBlockNode*)nodes[2],
            (ASTExportNode*)nodes[0]
    );
}