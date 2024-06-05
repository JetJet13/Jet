//
// Created by Johny Georges on 2024-04-22.
//

#include "class-property-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-init-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-with-type-node.h"

ASTNode* ClassPropertyInitReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() > 2) {
        throw std::invalid_argument("unable to reduce to class property init since nodes list size is > 2");
    }

    auto assignmentOperator = std::optional<ASTAssignmentOperatorNode*>();
    if (nodes.size() == 2) {
        assignmentOperator = (ASTAssignmentOperatorNode*)nodes[1];
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_NODE)) {
        auto classPropertyDefinition = (ASTClassPropertyDefinitionNode*)nodes[0];
        return new ASTClassPropertyInitNode(
                classPropertyDefinition->getAccessModifier(),
                classPropertyDefinition->getPropertyName(),
                classPropertyDefinition->getStatic(),
                classPropertyDefinition->getConstant(),
                assignmentOperator
        );
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE)) {
        auto classPropertyDefinitionWithType = (ASTClassPropertyDefinitionWithTypeNode*)nodes[0];
        return new ASTClassPropertyInitNode(
                classPropertyDefinitionWithType->getClassPropertyDefinition()->getAccessModifier(),
                classPropertyDefinitionWithType->getClassPropertyDefinition()->getPropertyName(),
                classPropertyDefinitionWithType->getClassPropertyDefinition()->getStatic(),
                classPropertyDefinitionWithType->getClassPropertyDefinition()->getConstant(),
                assignmentOperator,
                classPropertyDefinitionWithType->getColon(),
                classPropertyDefinitionWithType->getType()
        );
    }

    throw std::invalid_argument("unable to reduce to class property init since nodes list is incompatible");
}