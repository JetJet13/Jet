//
// Created by Johny Georges on 2024-04-10.
//

#include "variable-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-definition-node.h"

ASTNode* VariableDefinitionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to var definition node since nodes list is not 2");
    }

    return new ASTVariableDefinitionNode(
            (ASTVariableTypeNode*)nodes[0],
            (ASTIdentifierNode*)nodes[1]
    );
}