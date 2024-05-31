//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-method-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTClassMethodNameNode::getNodeType() {
    return AST_CLASS_METHOD_NAME_NODE;
}

std::string ASTClassMethodNameNode::toString() {
    return "CLASS_METHOD_NAME";
}

std::string ASTClassMethodNameNode::toSourceCode() {
    Logger::log(this->getId());
}