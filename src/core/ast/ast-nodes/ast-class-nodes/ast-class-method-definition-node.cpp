//
// Created by Johny Georges on 2024-04-26.
//

#include "ast-class-method-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTClassMethodDefinitionNode::ASTClassMethodDefinitionNode(ASTAccessModifierNode* accessModifier, ASTClassMethodNameNode* methodName, bool isStatic) {
    _accessModifier = accessModifier;
    _methodName = methodName;
    _isStatic = isStatic;
    _children.push_back(_accessModifier);
    _children.push_back(_methodName);
}

ASTAccessModifierNode* ASTClassMethodDefinitionNode::getAccessModifier() {
    return _accessModifier;
}

ASTClassMethodNameNode* ASTClassMethodDefinitionNode::getMethodName() {
    return _methodName;
}

bool ASTClassMethodDefinitionNode::isStatic() {
    return _isStatic;
}

ASTNodeType ASTClassMethodDefinitionNode::getNodeType() {
    return AST_CLASS_METHOD_DEFINITION_NODE;
}

std::string ASTClassMethodDefinitionNode::toString() {
    return "CLASS_METHOD_DEFINITION";
}

bool ASTClassMethodDefinitionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = (ASTClassMethodDefinitionNode*)other;
    return this->getAccessModifier()->isSameAs(otherNode->getAccessModifier()) &&
           this->getMethodName()->isSameAs(otherNode->getMethodName()) &&
           this->isStatic() == otherNode->isStatic();
}

void ASTClassMethodDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _accessModifier->print();
    _methodName->print();
    Logger::log("isStatic -", _isStatic);
    Logger::log("----------");
}