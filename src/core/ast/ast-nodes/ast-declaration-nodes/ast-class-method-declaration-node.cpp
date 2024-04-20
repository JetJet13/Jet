//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-method-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassMethodDeclarationNode::ASTClassMethodDeclarationNode(ASTClassMethodNameNode* name, ASTFunctionParameterListNode* parameters, std::optional<ASTTypeNode*> returnType, ASTFunctionBlockNode* content) {
    _name = name;
    _content = content;
    _returnType = returnType;
    _parameters = parameters;
}

ASTFunctionParameterListNode* ASTClassMethodDeclarationNode::getParameters() {
    return _parameters;
}

ASTClassMethodNameNode* ASTClassMethodDeclarationNode::getName() {
    return _name;
}

std::optional<ASTTypeNode*> ASTClassMethodDeclarationNode::getReturnType() {
    return _returnType;
}

ASTFunctionBlockNode* ASTClassMethodDeclarationNode::getContent() {
    return _content;
}

unsigned long ASTClassMethodDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

ASTNodeType ASTClassMethodDeclarationNode::getNodeType() {
    return AST_CLASS_METHOD_DECLARATION_NODE;
}

std::string ASTClassMethodDeclarationNode::toString() {
    return "CLASS_METHOD_DECLARATION";
}

bool ASTClassMethodDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassMethodDeclarationNode*)other;

    if (!_returnType.has_value() && otherNode->getReturnType().has_value() ||
        _returnType.has_value() && !otherNode->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && otherNode->getReturnType().has_value() &&
        !_returnType.value()->isSameAs(otherNode->getReturnType().value())) {
        return false;
    }

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getContent()->isSameAs(otherNode->getContent());
}

void ASTClassMethodDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    if (_returnType) {
        _returnType.value()->print();
    }
    _content->print();
    Logger::log("----------");
}