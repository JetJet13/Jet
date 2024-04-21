//
// Created by Johny Georges on 2024-04-20.
//

#include "class-property-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"

ASTNode* ClassPropertyDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() < 4 || nodes.size() > 8) {
        throw std::invalid_argument("unable to reduce to class property declaration since nodes list size is < 4 or > 8");
    }

    return new ASTClassPropertyDeclarationNode(
            (ASTAccessModifierNode*)nodes[0],
            this->getPropertyName(&nodes),
            this->getIsStatic(&nodes),
            this->getIsConstant(&nodes),
            this->getType(&nodes),
            this->getInitializer(&nodes)
    );
}

ASTClassPropertyNameNode* ClassPropertyDeclarationReducerStrategy::getPropertyName(std::vector<ASTNode*>* nodes) {
    if (nodes->at(3)->is(AST_CLASS_PROPERTY_NAME_NODE)) {
        return (ASTClassPropertyNameNode*)nodes->at(3);
    } else if (nodes->at(2)->is(AST_CLASS_PROPERTY_NAME_NODE)) {
        return (ASTClassPropertyNameNode*)nodes->at(2);
    } else {
        return (ASTClassPropertyNameNode*)nodes->at(1);
    }
}

bool ClassPropertyDeclarationReducerStrategy::getIsStatic(std::vector<ASTNode*>* nodes) {
    if (nodes->at(1)->is(AST_STATIC_NODE)) {
        return true;
    }
    return false;
}

bool ClassPropertyDeclarationReducerStrategy::getIsConstant(std::vector<ASTNode*>* nodes) {
    if (nodes->at(1)->is(AST_CONST_NODE) || nodes->at(2)->is(AST_CONST_NODE)) {
        return true;
    }
    return false;
}

std::optional<ASTTypeNode*> ClassPropertyDeclarationReducerStrategy::getType(std::vector<ASTNode*>* nodes) {
    if (nodes->at(5)->is(AST_TYPE_NODE)) {
        return (ASTTypeNode*)nodes->at(5);
    } else if (nodes->at(4)->is(AST_TYPE_NODE)) {
        return (ASTTypeNode*)nodes->at(4);
    } else if (nodes->at(3)->is(AST_TYPE_NODE)) {
        return (ASTTypeNode*)nodes->at(3);
    } else {
        return {};
    }
}

std::optional<ASTExpressionNode*> ClassPropertyDeclarationReducerStrategy::getInitializer(std::vector<ASTNode*>* nodes) {
    if (nodes->at(6)->is(AST_ASSIGNMENT_OPERATOR_NODE)) {
        return this->createExpressionNode(nodes->at(7));
    } else if (nodes->at(5)->is(AST_ASSIGNMENT_OPERATOR_NODE)) {
        return this->createExpressionNode(nodes->at(6));
    } else if (nodes->at(4)->is(AST_ASSIGNMENT_OPERATOR_NODE)) {
        return this->createExpressionNode(nodes->at(5));
    } else if (nodes->at(3)->is(AST_ASSIGNMENT_OPERATOR_NODE)) {
        return this->createExpressionNode(nodes->at(4));
    } else if (nodes->at(2)->is(AST_ASSIGNMENT_OPERATOR_NODE)) {
        return this->createExpressionNode(nodes->at(3));
    } else {
        return {};
    }
}