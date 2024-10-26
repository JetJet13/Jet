//
// Created by Johny Georges on 2024-03-22.
//

#include "procedure-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

ASTNode* ProcedureDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to procedure declaration since nodes list is not of size 2 or 3");
    }


    if (nodes.size() == 2) {
        return new ASTProcedureDeclarationNode(
                (ASTProcedureDefinitionNode*)nodes[0],
                (ASTFunctionBlockNode*)nodes[1]
        );
    }

    return new ASTProcedureDeclarationNode(
            (ASTProcedureDefinitionNode*)nodes[1],
            (ASTFunctionBlockNode*)nodes[2],
            (ASTExportNode*)nodes[0]
    );
}