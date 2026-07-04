//
// Created by Johny Georges on 2024-04-22.
//

#include "class-property-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-init-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-with-type-node.h"

std::shared_ptr<ASTNode> ClassPropertyInitReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() > 2) {
        throw std::invalid_argument("unable to reduce to class property init since nodes list size is > 2");
    }

    auto assignmentOperator = std::optional<std::shared_ptr<ASTAssignmentOperatorNode>>();
    if (nodes.size() == 2) {
        assignmentOperator = std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1]);
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_NODE)) {
        auto classPropertyDefinition = std::dynamic_pointer_cast<ASTClassPropertyDefinitionNode>(nodes[0]);
        return std::make_shared<ASTClassPropertyInitNode>(
                classPropertyDefinition->getAccessModifier(),
                classPropertyDefinition->getPropertyName(),
                classPropertyDefinition->getStatic(),
                classPropertyDefinition->getConstant(),
                assignmentOperator
        );
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE)) {
        auto classPropertyDefinitionWithType = std::dynamic_pointer_cast<ASTClassPropertyDefinitionWithTypeNode>(nodes[0]);
        return std::make_shared<ASTClassPropertyInitNode>(
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