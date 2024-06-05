//
// Created by Johny Georges on 2024-05-31.
//

#include "ast-procedure-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTProcedureTypeNode::ASTProcedureTypeNode(ASTProcedureLambdaTypeParameterListNode* parameterList) {
    _parameterList = parameterList;
    _children.push_back(_parameterList);
}

ASTTypeParameterListNode* ASTProcedureTypeNode::getParameterList() {
    return _parameterList->getTypeParameterList();
}

ASTNodeType ASTProcedureTypeNode::getNodeType() {
    return AST_PROCEDURE_TYPE_NODE;
}

std::string ASTProcedureTypeNode::toString() {
    return "PROCEDURE_TYPE";
}

bool ASTProcedureTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTProcedureTypeNode*)other;

    return this->getParameterList()->isSameAs(otherNode->getParameterList());
}

void ASTProcedureTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    Logger::log("----------");
}

std::string ASTProcedureTypeNode::toSourceCode() {
    return _parameterList->toSourceCode();
}