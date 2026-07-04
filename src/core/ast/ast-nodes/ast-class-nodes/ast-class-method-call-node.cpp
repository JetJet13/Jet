//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-method-call-node.h"
#include "../../../../shared/utils/logger/logger.h"

void ASTClassMethodCallNode::setTypeSignature(std::shared_ptr<ClassMethodTypeSignature> classMethodTypeSignature) {
    _typeSignature = classMethodTypeSignature;
}

std::shared_ptr<ClassMethodTypeSignature> ASTClassMethodCallNode::getMethodTypeSignature() {
    return std::dynamic_pointer_cast<ClassMethodTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTClassMethodCallNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTClassMethodCallNode::getNodeType() {
    return AST_CLASS_METHOD_CALL_NODE;
}

std::string ASTClassMethodCallNode::toString() {
    return "CLASS_METHOD_CALL";
}