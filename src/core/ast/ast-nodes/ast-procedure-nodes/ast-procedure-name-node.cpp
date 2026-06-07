//
// Created by Johny Georges on 2026-06-06.
//

#include "ast-procedure-name-node.h"

ASTNodeType ASTProcedureNameNode::getNodeType() {
    return AST_PROCEDURE_NAME_NODE;
}

std::string ASTProcedureNameNode::toString() {
    return "PROCEDURE_NAME";
}

std::string ASTProcedureNameNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}