//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-method-call-node.h"
#include "../../../../shared/utils/logger/logger.h"

void ASTClassMethodCallNode::setTypeSignature(ClassMethodTypeSignature* classMethodTypeSignature) {
    _typeSignature = classMethodTypeSignature;
}

ClassMethodTypeSignature* ASTClassMethodCallNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTClassMethodCallNode::getNodeType() {
    return AST_CLASS_METHOD_CALL_NODE;
}

std::string ASTClassMethodCallNode::toString() {
    return "CLASS_METHOD_CALL";
}