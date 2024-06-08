//
// Created by Johny Georges on 2024-02-17.
//

#include "variable-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-init-node.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-definition-node.h"

ASTNode* VariableInitReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        return new ASTVariableInitNode(
                ((ASTVariableDefinitionNode*)nodes[0])->getVarTypeNode(),
                ((ASTVariableDefinitionNode*)nodes[0])->getIdentifierNode(),
                (ASTAssignmentOperatorNode*)nodes[1]
        );
    }

    if (nodes.size() == 4) {
        return new ASTVariableInitNode(
                ((ASTVariableDefinitionNode*)nodes[0])->getVarTypeNode(),
                ((ASTVariableDefinitionNode*)nodes[0])->getIdentifierNode(),
                (ASTAssignmentOperatorNode*)nodes[3],
                (ASTColonNode*)nodes[1],
                (ASTTypeNode*)nodes[2]
        );
    }

    throw std::invalid_argument("unable to reduce to var init node since nodes list is not 2 or 4");
}
