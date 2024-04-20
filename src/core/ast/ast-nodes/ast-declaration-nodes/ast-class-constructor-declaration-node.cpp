//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-constructor-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassConstructorDeclarationNode::ASTClassConstructorDeclarationNode(ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content) {
    _content = content;
    _parameters = parameters;
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