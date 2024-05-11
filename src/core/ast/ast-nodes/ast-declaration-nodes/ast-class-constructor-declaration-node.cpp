//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-constructor-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassConstructorDeclarationNode::ASTClassConstructorDeclarationNode(ASTConstructorNode* constructor, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content) {
    _constructor = constructor;
    _content = content;
    _parameters = parameters;
    _children.push_back(_constructor);
    _children.push_back(_content);
    _children.push_back(_parameters);
}

ASTConstructorNode* ASTClassConstructorDeclarationNode::getConstructor() {
    return _constructor;
}

ASTFunctionParameterListNode* ASTClassConstructorDeclarationNode::getParameters() {
    return _parameters;
}

ASTFunctionBlockNode* ASTClassConstructorDeclarationNode::getContent() {
    return _content;
}

unsigned long ASTClassConstructorDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

ASTNodeType ASTClassConstructorDeclarationNode::getNodeType() {
    return AST_CLASS_CONSTRUCTOR_DECLARATION_NODE;
}

std::string ASTClassConstructorDeclarationNode::toString() {
    return "CLASS_CONSTRUCTOR_DECLARATION";
}

bool ASTClassConstructorDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassConstructorDeclarationNode*)other;

    return this->getParameters()->isSameAs(otherNode->getParameters()) &&
           this->getContent()->isSameAs(otherNode->getContent());
}

void ASTClassConstructorDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameters->print();
    _content->print();
    Logger::log("----------");
}
