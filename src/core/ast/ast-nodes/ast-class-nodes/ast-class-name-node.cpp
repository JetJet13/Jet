//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTClassNameNode::getNodeType() {
    return AST_CLASS_NAME_NODE;
}

std::string ASTClassNameNode::toString() {
    return "CLASS_NAME";
}

std::string ASTClassNameNode::toSourceCode() {
    Logger::log(this->getId());
}