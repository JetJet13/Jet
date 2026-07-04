//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_AST_NODE_TYPE_SIGNATURE_RESULT_H
#define JETLANG_AST_NODE_TYPE_SIGNATURE_RESULT_H

#include "../../../type-signature/type-signature.h"
#include "../../../ast/ast-nodes/ast-node.h"

struct ASTNodeTypeSignatureResult {
    std::shared_ptr<ASTNode> node;
    TypeSignature* typeSignature;
};

#endif //JETLANG_AST_NODE_TYPE_SIGNATURE_RESULT_H
