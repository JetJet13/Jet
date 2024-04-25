//
// Created by Johny Georges on 2024-04-22.
//

#include "class-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-block-node.h"

ASTNode* ClassBlockReducerStrategy::execute(std::vector<ASTNode*> nodes) {
        throw std::logic_error("ClassBlockReducerStrategy invoked");

    auto classBlock = new ASTClassBlockNode();
    for (auto node : nodes) {
        if (node->is(AST_CLASS_PROPERTY_NODE)) {
            classBlock->addProperty((ASTClassPropertyNode*)node);
        }
        if (node->is(AST_CLASS_METHOD_NODE)) {
            classBlock->addMethod((ASTClassMethodNode*)node);
        }
        if (node->is(AST_CLASS_CONSTRUCTOR_NODE)) {
            classBlock->addConstructor((ASTClassConstructorNode*)node);
        }
    }

    return classBlock;
}