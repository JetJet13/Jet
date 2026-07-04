//
// Created by Johny Georges on 2024-02-17.
//

#include "variable-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-init-node.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-definition-node.h"

std::shared_ptr<ASTNode> VariableInitReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 2) {
        return std::make_shared<ASTVariableInitNode>(
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getVarTypeNode(),
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getIdentifierNode(),
                std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
        );
    }

    if (nodes.size() == 4) {
        return std::make_shared<ASTVariableInitNode>(
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getVarTypeNode(),
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getIdentifierNode(),
                std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[3]),
                std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
        );
    }

    throw std::invalid_argument("unable to reduce to var init node since nodes list is not 2 or 4");
}
