//
// Created by Johny Georges on 2024-04-22.
//

#include "class-property-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-node.h"

ASTNode* ClassPropertyDefinitionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() < 2 || nodes.size() > 4) {
        throw std::invalid_argument("unable to reduce to class property definition since nodes list size is < 2 or > 4");
    }

    return new ASTClassPropertyDefinitionNode(
            (ASTAccessModifierNode*)nodes[0],
            this->getPropertyName(&nodes),
            this->getIsStatic(&nodes),
            this->getIsConstant(&nodes)
    );
}

ASTClassPropertyNameNode* ClassPropertyDefinitionReducerStrategy::getPropertyName(std::vector<ASTNode*>* nodes) {
    if (nodes->size() == 4 && nodes->at(3)->is(AST_IDENTIFIER_NODE)) {
        return new ASTClassPropertyNameNode(((ASTIdentifierNode*)nodes->at(3))->getIdentifier());
    } else if (nodes->size() == 3 && nodes->at(2)->is(AST_IDENTIFIER_NODE)) {
        return new ASTClassPropertyNameNode(((ASTIdentifierNode*)nodes->at(2))->getIdentifier());
    } else {
        return new ASTClassPropertyNameNode(((ASTIdentifierNode*)nodes->at(1))->getIdentifier());
    }
}

bool ClassPropertyDefinitionReducerStrategy::getIsStatic(std::vector<ASTNode*>* nodes) {
    return nodes->at(1)->is(AST_STATIC_NODE);
}

bool ClassPropertyDefinitionReducerStrategy::getIsConstant(std::vector<ASTNode*>* nodes) {
    if (nodes->size() > 2) {
        return nodes->at(1)->is(AST_CONST_NODE) || nodes->at(2)->is(AST_CONST_NODE);
    }
    return false;
}