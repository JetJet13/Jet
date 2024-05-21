//
// Created by Johny Georges on 2024-04-22.
//

#include "class-property-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-init-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-with-type-node.h"
#include "../../../../../../shared/utils/logger/logger.h"

ASTNode* ClassPropertyInitReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() > 2) {
        throw std::invalid_argument("unable to reduce to class property init since nodes list size is > 2");
    }

    Logger::log("ClassPropertyInitReducerStrategy");
    for (auto node: nodes) {
        node->print();
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_NODE)) {
        Logger::log("creating AST_CLASS_PROPERTY_DEFINITION_NODE");
        auto classPropertyDefinition = (ASTClassPropertyDefinitionNode*)nodes[0];
        return new ASTClassPropertyInitNode(
                classPropertyDefinition->getAccessModifier(),
                classPropertyDefinition->getPropertyName(),
                classPropertyDefinition->isStatic(),
                classPropertyDefinition->isConstant()
        );
    }

    if (nodes[0]->is(AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE)) {
        Logger::log("creating AST_CLASS_PROPERTY_DEFINITION_WITH_TYPE_NODE");
        auto classPropertyDefinitionWithType = (ASTClassPropertyDefinitionWithTypeNode*)nodes[0];
        return new ASTClassPropertyInitNode(
                classPropertyDefinitionWithType->getClassPropertyDefinition()->getAccessModifier(),
                classPropertyDefinitionWithType->getClassPropertyDefinition()->getPropertyName(),
                classPropertyDefinitionWithType->getClassPropertyDefinition()->isStatic(),
                classPropertyDefinitionWithType->getClassPropertyDefinition()->isConstant(),
                classPropertyDefinitionWithType->getType()
        );
    }

    throw std::invalid_argument("unable to reduce to class property init since nodes list is incompatible");
}