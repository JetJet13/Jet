//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-method-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassMethodDeclarationNode::ASTClassMethodDeclarationNode(ASTClassMethodDefinitionNode* classMethodDefinition, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content, std::optional<ASTTypeNode*> returnType) {
    _classMethodDefinition = classMethodDefinition;
    _content = content;
    _returnType = returnType;
    _parameters = parameters;

    _children.push_back(_classMethodDefinition);
    _children.push_back(_content);
    if (_returnType) {
        _children.push_back(_returnType.value());
    }
    _children.push_back(_parameters);
}

ASTClassMethodDefinitionNode* ASTClassMethodDeclarationNode::getClassMethodDefinition() {
    return _classMethodDefinition;
}

ASTFunctionParameterListNode* ASTClassMethodDeclarationNode::getParameters() {
    return _parameters;
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

    return this->getClassMethodDefinition()->isSameAs(otherNode->getClassMethodDefinition()) &&
           this->getParameters()->isSameAs(otherNode->getParameters()) &&
           this->getContent()->isSameAs(otherNode->getContent());
}

void ASTClassMethodDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _classMethodDefinition->print();
    _parameters->print();
    if (_returnType) {
        _returnType.value()->print();
    }
    _content->print();
    Logger::log("----------");
}