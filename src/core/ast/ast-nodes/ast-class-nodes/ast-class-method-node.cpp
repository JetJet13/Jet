//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-method-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassMethodNode::ASTClassMethodNode(ASTAccessModifierNode* accessModifier, ASTClassMethodNameNode* name, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content, std::optional<ASTTypeNode*> returnType) {
    _accessModifier = accessModifier;
    _name = name;
    _content = content;
    _returnType = returnType;
    _parameters = parameters;
}

ASTAccessModifierNode* ASTClassMethodNode::getAccessModifier() {
    return _accessModifier;
}

ASTFunctionParameterListNode* ASTClassMethodNode::getParameters() {
    return _parameters;
}

ASTClassMethodNameNode* ASTClassMethodNode::getName() {
    return _name;
}

std::optional<ASTTypeNode*> ASTClassMethodNode::getReturnType() {
    return _returnType;
}

ASTFunctionBlockNode* ASTClassMethodNode::getContent() {
    return _content;
}

unsigned long ASTClassMethodNode::numParameters() {
    return _parameters->numParameters();
}

ASTNodeType ASTClassMethodNode::getNodeType() {
    return AST_CLASS_METHOD_NODE;
}

std::string ASTClassMethodNode::toString() {
    return "CLASS_METHOD_DECLARATION";
}

bool ASTClassMethodNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassMethodNode*)other;

    if (!_returnType.has_value() && otherNode->getReturnType().has_value() ||
        _returnType.has_value() && !otherNode->getReturnType().has_value()) {
        return false;
    }

    if (_returnType.has_value() && otherNode->getReturnType().has_value() &&
        !_returnType.value()->isSameAs(otherNode->getReturnType().value())) {
        return false;
    }

    return this->getAccessModifier()->isSameAs(otherNode->getAccessModifier()) &&
           this->getName()->isSameAs(otherNode->getName()) &&
           this->getParameters()->isSameAs(otherNode->getParameters()) &&
           this->getContent()->isSameAs(otherNode->getContent());
}

void ASTClassMethodNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    if (_returnType) {
        _returnType.value()->print();
    }
    _content->print();
    Logger::log("----------");
}