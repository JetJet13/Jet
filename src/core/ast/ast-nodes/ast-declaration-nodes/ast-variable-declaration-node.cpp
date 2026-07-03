//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-variable-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTVariableDeclarationNode::ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer, std::optional<ASTExportNode*> exportKeyword) {
    _varInit = varInit;
    _initializer = initializer;
    _exportKeyword = exportKeyword;
    _varInit->setParentNode(this);
    _initializer->setParentNode(this);
    _children.push_back(_varInit);
    _children.push_back(_initializer);
    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }

}

ASTVariableInitNode* ASTVariableDeclarationNode::getVarInitNode() {
    return _varInit;
}

ASTExpressionNode* ASTVariableDeclarationNode::getInitializerNode() {
    return _initializer;
}

void ASTVariableDeclarationNode::markAsCaptured() {
    _captureCount++;
}

unsigned long ASTVariableDeclarationNode::getCaptureCount() {
    return _captureCount;
}

bool ASTVariableDeclarationNode::isConst() {
    return _varInit->isConst();
}

bool ASTVariableDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

bool ASTVariableDeclarationNode::isCaptured() {
    return _captureCount > 0;
}

void ASTVariableDeclarationNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTVariableDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTVariableDeclarationNode::getStartPosition() {
    return _varInit->getStartPosition();
}

Position* ASTVariableDeclarationNode::getEndPosition() {
    return _initializer->getEndPosition();
}

ASTNodeType ASTVariableDeclarationNode::getNodeType() {
    return AST_VARIABLE_DECLARATION_NODE;
}

std::string ASTVariableDeclarationNode::toString() {
    return "VARIABLE_DECLARATION";
}

bool ASTVariableDeclarationNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }

    auto otherNode = (ASTVariableDeclarationNode*)other;
    if (!this->isExportable() && otherNode->isExportable() || this->isExportable() && !otherNode->isExportable()) {
        return false;
    }

    return this->getVarInitNode()->isSameAs(otherNode->getVarInitNode()) &&
           this->getInitializerNode()->isSameAs(otherNode->getInitializerNode());
}

void ASTVariableDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_exportKeyword) {
        _exportKeyword.value()->print();
    }
    _varInit->print();
    _initializer->print();
    Logger::log("----------");
}

std::string ASTVariableDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    if (_exportKeyword) {
        sourceCodeBuilder.add(_exportKeyword.value());
    }
    sourceCodeBuilder.add(_varInit);
    sourceCodeBuilder.add(_initializer);
    return sourceCodeBuilder.build();
}