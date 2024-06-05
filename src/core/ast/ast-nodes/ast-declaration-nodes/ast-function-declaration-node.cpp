//
// Created by Johny Georges on 2024-03-18.
//

#include "ast-function-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionDeclarationNode::ASTFunctionDeclarationNode(ASTFunctionNode* functionKeyword, ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTTypeNode* returnType, ASTFunctionBlockNode* content) {
    _functionKeyword = functionKeyword;
    _name = name;
    _block = content;
    _returnType = returnType;
    _parameters = parameters;
    _children.push_back(_functionKeyword);
    _children.push_back(_name);
    _children.push_back(_block);
    _children.push_back(_returnType);
    _children.push_back(_parameters);
}

ASTFunctionParameterListNode* ASTFunctionDeclarationNode::getParameters() {
    return _parameters;
}

ASTFunctionNameNode* ASTFunctionDeclarationNode::getName() {
    return _name;
}

ASTTypeNode* ASTFunctionDeclarationNode::getReturnType() {
    return _returnType;
}

ASTFunctionBlockNode* ASTFunctionDeclarationNode::getBlock() {
    return _block;
}

unsigned long ASTFunctionDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

void ASTFunctionDeclarationNode::setTypeSignature(FunctionTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

FunctionTypeSignature* ASTFunctionDeclarationNode::getTypeSignature() {
    return _typeSignature;
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
            this->getReturnType()->isSameAs(otherNode->getReturnType()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTFunctionDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _parameters->print();
    _returnType->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTFunctionDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_functionKeyword)
    ->addWithWhitespace(_name)
    ->addWithWhitespace(_parameters)
    ->addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}