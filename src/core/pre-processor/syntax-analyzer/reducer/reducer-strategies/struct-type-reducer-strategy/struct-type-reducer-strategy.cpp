//
// Created by Johny Georges on 2025-06-28.
//

#include "struct-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-struct-type-nodes/ast-struct-type-node.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* StructTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto structTypeNode = new ASTStructTypeNode(
            (ASTStructTypeStartNode*)nodes[0],
            (ASTStructTypeEndNode*)nodes[nodes.size() - 1]
    );
    for (auto node : nodes) {
        if (node->is(AST_STRUCT_TYPE_KEY_NODE)) {
            structTypeNode->addKeyValueType((ASTStructTypeKeyValueNode*)node);
        }

        if (node->is(AST_COMMA_NODE)) {
            structTypeNode->addComma((ASTCommaNode*)node);
        }
    }
    return ASTTypeNodeFactory::createStructTypeNode(structTypeNode);
}