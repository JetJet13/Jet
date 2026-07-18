//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-method-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassMethodDeclarationNode::ASTClassMethodDeclarationNode(std::shared_ptr<ASTClassMethodDefinitionNode> classMethodDefinition, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> content) {
    _classMethodDefinition = classMethodDefinition;
    _block = content;
    _typeColon = {};
    _returnType = {};
    _parameters = parameters;
    _children.push_back(_classMethodDefinition);
    _children.push_back(_parameters);
    _children.push_back(_block);
}

ASTClassMethodDeclarationNode::ASTClassMethodDeclarationNode(std::shared_ptr<ASTClassMethodDefinitionNode> classMethodDefinition, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> content, std::shared_ptr<ASTTypeColonNode> typeColon, std::shared_ptr<ASTTypeNode> returnType) {
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

std::shared_ptr<ASTClassMethodDefinitionNode> ASTClassMethodDeclarationNode::getClassMethodDefinition() {
    return _classMethodDefinition;
}

std::shared_ptr<ASTFunctionParameterListNode> ASTClassMethodDeclarationNode::getParameters() {
    return _parameters;
}

std::optional<std::shared_ptr<ASTTypeNode>> ASTClassMethodDeclarationNode::getReturnType() {
    return _returnType;
}

std::shared_ptr<ASTFunctionBlockNode> ASTClassMethodDeclarationNode::getBlock() {
    return _block;
}

bool ASTClassMethodDeclarationNode::isStatic() {
    return _classMethodDefinition->isStatic();
}

unsigned long ASTClassMethodDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

void ASTClassMethodDeclarationNode::setTypeSignature(std::shared_ptr<ClassMethodTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<ClassMethodTypeSignature> ASTClassMethodDeclarationNode::getMethodTypeSignature() {
    return std::dynamic_pointer_cast<ClassMethodTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTClassMethodDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTClassMethodDeclarationNode::getStartPosition() {
    return _classMethodDefinition->getStartPosition();
}

std::shared_ptr<Position> ASTClassMethodDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTClassMethodDeclarationNode::getNodeType() {
    return AST_CLASS_METHOD_DECLARATION_NODE;
}

std::string ASTClassMethodDeclarationNode::toString() {
    return "CLASS_METHOD_DECLARATION";
}

bool ASTClassMethodDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassMethodDeclarationNode>(other);

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
    return sourceCodeBuilder.build();
}