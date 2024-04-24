//
// Created by Johny Georges on 2024-04-22.
//

#include "class-property-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-init-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-with-type-node.h"

ASTNode* ClassPropertyInitReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property init since nodes list size is not 2");
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_NODE)) {
        return new ASTClassPropertyInitNode(
                ((ASTClassPropertyDefinitionNode*)nodes[0])->getAccessModifier(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->getPropertyName(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->isStatic(),
                ((ASTClassPropertyDefinitionNode*)nodes[0])->isConstant()
        );
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE)) {
        return new ASTClassPropertyInitNode(
                ((ASTClassPropertyDefinitionWithTypeNode*)nodes[0])->getClassPropertyDefinition()->getAccessModifier(),
                ((ASTClassPropertyDefinitionWithTypeNode*)nodes[0])->getClassPropertyDefinition()->getPropertyName(),
                ((ASTClassPropertyDefinitionWithTypeNode*)nodes[0])->getClassPropertyDefinition()->isStatic(),
                ((ASTClassPropertyDefinitionWithTypeNode*)nodes[0])->getClassPropertyDefinition()->isConstant(),
                ((ASTClassPropertyDefinitionWithTypeNode*)nodes[0])->getType()
        );
    }

    throw std::invalid_argument("unable to reduce to class property init since nodes list is incompatible");
}