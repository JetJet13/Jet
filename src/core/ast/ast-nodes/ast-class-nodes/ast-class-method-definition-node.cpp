//
// Created by Johny Georges on 2024-04-26.
//

#include "ast-class-method-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassMethodDefinitionNode::ASTClassMethodDefinitionNode(ASTAccessModifierNode* accessModifier, ASTClassMethodNameNode* methodName, std::optional<ASTStaticNode*> staticKeyword) {
    _accessModifier = accessModifier;
    _methodName = methodName;
    _staticKeyword = staticKeyword;
    _children.push_back(_accessModifier);
    _children.push_back(_methodName);
    if (_staticKeyword) {
        _children.push_back(_staticKeyword.value());
    }
}

ASTAccessModifierNode* ASTClassMethodDefinitionNode::getAccessModifier() {
    return _accessModifier;
}

ASTClassMethodNameNode* ASTClassMethodDefinitionNode::getMethodName() {
    return _methodName;
}

bool ASTClassMethodDefinitionNode::isStatic() {
    return _staticKeyword.has_value();
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
    Logger::log("isStatic -", this->isStatic());
    Logger::log("----------");
}

std::string ASTClassMethodDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_accessModifier);
    if (_staticKeyword) {
        sourceCodeBuilder.addWithWhitespace(_staticKeyword.value());
    }
    sourceCodeBuilder.addWithWhitespace(_methodName);
    return sourceCodeBuilder.build();
}