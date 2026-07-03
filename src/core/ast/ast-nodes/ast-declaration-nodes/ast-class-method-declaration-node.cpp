//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-method-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassMethodDeclarationNode::ASTClassMethodDeclarationNode(ASTClassMethodDefinitionNode* classMethodDefinition, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content) {
    _classMethodDefinition = classMethodDefinition;
    _block = content;
    _typeColon = {};
    _returnType = {};
    _parameters = parameters;
    _children.push_back(_classMethodDefinition);
    _children.push_back(_parameters);
    _children.push_back(_block);
}

ASTClassMethodDeclarationNode::ASTClassMethodDeclarationNode(ASTClassMethodDefinitionNode* classMethodDefinition, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content, ASTTypeColonNode* typeColon, ASTTypeNode* returnType) {
    _classMethodDefinition = classMethodDefinition;
    _block = content;
    _typeColon = typeColon;
    _returnType = returnType;
    _parameters = parameters;
    _children.push_back(_classMethodDefinition);
    _children.push_back(_parameters);
    _children.push_back(_typeColon.value());
    _children.push_back(_returnType.value());
    _children.push_back(_block);
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

ASTFunctionBlockNode* ASTClassMethodDeclarationNode::getBlock() {
    return _block;
}

bool ASTClassMethodDeclarationNode::isStatic() {
    return _classMethodDefinition->isStatic();
}

unsigned long ASTClassMethodDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

void ASTClassMethodDeclarationNode::setTypeSignature(ClassMethodTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ClassMethodTypeSignature* ASTClassMethodDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTClassMethodDeclarationNode::getStartPosition() {
    return _classMethodDefinition->getStartPosition();
}

Position* ASTClassMethodDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTClassMethodDeclarationNode::getNodeType() {
    return AST_CLASS_METHOD_DECLARATION_NODE;
}

std::string ASTClassMethodDeclarationNode::toString() {
    return "CLASS_METHOD_DECLARATION";
}

bool ASTClassMethodDeclarationNode::isSameAs(ASTNode* other) {
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
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTClassMethodDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _classMethodDefinition->print();
    _parameters->print();
    if (_returnType) {
        _typeColon.value()->print();
        _returnType.value()->print();
    }
    _block->print();
    Logger::log("----------");
}

std::string ASTClassMethodDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classMethodDefinition)
    ->add(_parameters);
    if (_returnType) {
        sourceCodeBuilder
        .add(_typeColon.value())
        ->add(_returnType.value());
    }
    sourceCodeBuilder.add(_block);
    return sourceCodeBuilder.build();
}