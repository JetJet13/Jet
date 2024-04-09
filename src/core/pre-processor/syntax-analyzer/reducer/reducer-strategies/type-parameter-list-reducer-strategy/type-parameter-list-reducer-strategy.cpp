//
// Created by Johny Georges on 2024-04-04.
//

#include "type-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-parameter-list-node.h"


ASTNode* TypeParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto typeParameterListNode = new ASTTypeParameterListNode();
    for (auto node : nodes) {
        if (node->is(AST_TYPE_NODE)) {
            typeParameterListNode->addParameter((ASTTypeNode*)node);
        }
    }
    return typeParameterListNode;
}