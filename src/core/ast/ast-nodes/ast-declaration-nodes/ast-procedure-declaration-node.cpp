//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-procedure-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTProcedureDeclarationNode::ASTProcedureDeclarationNode(ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content) {
    _name = name;
    _content = content;
    _parameters = parameters;
    _children.push_back(_name);
    _children.push_back(_content);
    _children.push_back(_parameters);

}

ASTFunctionParameterListNode* ASTProcedureDeclarationNode::getParameters() {
    return _parameters;
}

ASTFunctionNameNode* ASTProcedureDeclarationNode::getName() {
    return _name;
}

ASTFunctionBlockNode* ASTProcedureDeclarationNode::getContent() {
    return _content;
}

unsigned long ASTProcedureDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

ASTNodeType ASTProcedureDeclarationNode::getNodeType() {
    return AST_PROCEDURE_DECLARATION_NODE;
}

std::string ASTProcedureDeclarationNode::toString() {
    return "PROCEDURE_DECLARATION";
}

bool ASTProcedureDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTProcedureDeclarationNode*)other;

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getContent()->isSameAs(otherNode->getContent());
}

void ASTProcedureDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    _content->print();
    Logger::log("----------");
}