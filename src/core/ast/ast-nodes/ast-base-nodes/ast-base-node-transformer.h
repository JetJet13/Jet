//
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_AST_BASE_NODE_TRANSFORMER_H
#define JETLANG_AST_BASE_NODE_TRANSFORMER_H

#include "../ast-node.h"
#include "ast-plus-base-node.h"
#include "ast-minus-base-node.h"
#include "../ast-array-nodes/ast-left-bracket-node.h"
#include "../ast-array-nodes/ast-right-bracket-node.h"
#include "../../../pre-processor/syntax-analyzer/handle/handle.h"

class ASTBaseNodeTransformer {
private:
    Handle* _handle;
public:
    ASTBaseNodeTransformer(Handle* handle);
    ASTNode* transformPlusBaseNode(ASTPlusBaseNode* astPlusBaseNode);
    ASTNode* transformMinusBaseNode(ASTMinusBaseNode* astMinusBaseNode);
};

#endif //JETLANG_AST_BASE_NODE_TRANSFORMER_H
