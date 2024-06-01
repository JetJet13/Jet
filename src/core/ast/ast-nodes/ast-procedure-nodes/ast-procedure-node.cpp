//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-procedure-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTProcedureNode::getNodeType() {
    return AST_PROCEDURE_NODE;
}

std::string ASTProcedureNode::toString() {
    return "PROCEDURE";
}