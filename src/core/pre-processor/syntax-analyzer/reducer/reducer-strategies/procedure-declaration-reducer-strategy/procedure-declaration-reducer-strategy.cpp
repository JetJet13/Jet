//
// Created by Johny Georges on 2024-03-22.
//

#include "procedure-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

std::shared_ptr<ASTNode> ProcedureDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to procedure declaration since nodes list is not of size 2 or 3");
    }


    if (nodes.size() == 2) {
        return std::make_shared<ASTProcedureDeclarationNode>(
                std::dynamic_pointer_cast<ASTProcedureDefinitionNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[1])
        );
    }

    return std::make_shared<ASTProcedureDeclarationNode>(
            std::dynamic_pointer_cast<ASTProcedureDefinitionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
    );
}