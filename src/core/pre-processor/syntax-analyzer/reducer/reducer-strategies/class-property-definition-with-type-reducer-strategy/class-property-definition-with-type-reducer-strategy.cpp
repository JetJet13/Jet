//
// Created by Johny Georges on 2024-04-24.
//

#include "class-property-definition-with-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-with-type-node.h"

ASTNode* ClassPropertyDefinitionWithTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to class property definition with type since nodes list size is not 3");
    }
    return new ASTClassPropertyDefinitionWithTypeNode(
            (ASTClassPropertyDefinitionNode*)nodes[0],
            (ASTTypeNode*)nodes[2]
    );
}