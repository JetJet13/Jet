//
// Created by Johny Georges on 2024-03-18.
//

#include "ast-function-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionDeclarationNode::ASTFunctionDeclarationNode(ASTFunctionDefinitionNode* functionDefinition, ASTFunctionBlockNode* content, std::optional<ASTExportNode*> exportKeyword) {
    _functionDefinition = functionDefinition;
    _block = content;
    _exportKeyword = exportKeyword;
    _children.push_back(_functionDefinition);
    _children.push_back(_block);
    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }
}

ASTFunctionParameterListNode* ASTFunctionDeclarationNode::getParameters() {
    return _functionDefinition->getParameters();
}

ASTFunctionNameNode* ASTFunctionDeclarationNode::getName() {
    return _functionDefinition->getName();
}

ASTTypeNode* ASTFunctionDeclarationNode::getReturnType() {
    return _functionDefinition->getReturnType();
}

ASTFunctionBlockNode* ASTFunctionDeclarationNode::getBlock() {
    return _block;
}

unsigned long ASTFunctionDeclarationNode::numParameters() {
    return _functionDefinition->numParameters();
}

void ASTFunctionDeclarationNode::setTypeSignature(FunctionTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

FunctionTypeSignature* ASTFunctionDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTFunctionDeclarationNode::getStartPosition() {
    return _functionDefinition->getStartPosition();
}

Position* ASTFunctionDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
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
    if (_exportKeyword) {
        _exportKeyword.value()->print();
    }
    _functionDefinition->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTFunctionDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    if (_exportKeyword) {
        sourceCodeBuilder.add(_exportKeyword.value())->addWithWhitespace(_functionDefinition);
    } else {
        sourceCodeBuilder.add(_functionDefinition);
    }
    sourceCodeBuilder.addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}