//
// Created by Johny Georges on 2024-04-22.
//

#include "class-property-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-init-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-node.h"

ASTNode* ClassPropertyInitReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        return new ASTClassPropertyInitNode(
                ((ASTClassPropertyDefinitionNode*)nodes[0])->getAccessModifier(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->getPropertyName(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->isStatic(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->isConstant()
        );
    }

    if (nodes.size() == 4) {
        return new ASTClassPropertyInitNode(
                ((ASTClassPropertyDefinitionNode*)nodes[0])->getAccessModifier(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->getPropertyName(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->isStatic(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->isConstant(),
                (ASTTypeNode*)nodes[2]
        );
    }

    throw std::invalid_argument("unable to reduce to class property init since nodes list size is not 2 or 4");
}