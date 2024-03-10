//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-base-node-transformer.h"

ASTBaseNodeTransformer::ASTBaseNodeTransformer(Handle* handle) {
    _handle = handle;
}

ASTNode* ASTBaseNodeTransformer::transformPlusBaseNode(ASTPlusBaseNode* astPlusBaseNode) {
    return astPlusBaseNode;
}

ASTNode* ASTBaseNodeTransformer::transformMinusBaseNode(ASTMinusBaseNode* astMinusBaseNode) {
    return astMinusBaseNode;
}