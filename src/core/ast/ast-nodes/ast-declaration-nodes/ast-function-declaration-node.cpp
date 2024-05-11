//
// Created by Johny Georges on 2024-03-18.
//

#include "ast-function-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionDeclarationNode::ASTFunctionDeclarationNode(ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTTypeNode* returnType, ASTFunctionBlockNode* content) {
    _name = name;
    _content = content;
    _returnType = returnType;
    _parameters = parameters;
    _children.push_back(_name);
    _children.push_back(_content);
    _children.push_back(_returnType);
    _children.push_back(_parameters);
}

ASTFunctionParameterListNode* ASTFunctionDeclarationNode::getParameters() {
    return _parameters;
}

ASTFunctionNameNode* ASTFunctionDeclarationNode::getName() {
    return _name;
}

ASTTypeNode* ASTFunctionDeclarationNode::getReturnType() {
    return _returnType;
}

ASTFunctionBlockNode* ASTFunctionDeclarationNode::getContent() {
    return _content;
}

unsigned long ASTFunctionDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

ASTNodeType ASTFunctionDeclarationNode::getNodeType() {
    return AST_FUNCTION_DECLARATION_NODE;
}

std::string ASTFunctionDeclarationNode::toString() {
    return "FUNCTION_DECLARATION";
}

bool ASTFunctionDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionDeclarationNode*)other;

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getReturnType()->isSameAs(otherNode->getReturnType()) &&
            this->getContent()->isSameAs(otherNode->getContent());
}

void ASTFunctionDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    _returnType->print();
    _content->print();
    Logger::log("----------");
}