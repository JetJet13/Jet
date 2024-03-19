//
// Created by Johny Georges on 2024-03-18.
//

#include "ast-function-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionDeclarationNode::ASTFunctionDeclarationNode(ASTIdentifierExpressionNode* name, ASTFunctionParameterListNode* parameters, ASTBlockNode* content) {
    _name = name;
    _content = content;
    _parameters = parameters;
}

ASTFunctionParameterListNode* ASTFunctionDeclarationNode::getParameters() {
    return _parameters;
}

ASTIdentifierExpressionNode* ASTFunctionDeclarationNode::getName() {
    return _name;
}

ASTBlockNode* ASTFunctionDeclarationNode::getContent() {
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
            this->getContent()->isSameAs(otherNode->getContent());
}

void ASTFunctionDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    _content->print();
    Logger::log("----------");
}