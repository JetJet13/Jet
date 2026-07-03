//
// Created by Johny Georges on 2024-03-12.
//

#include "ast-struct-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTStructExpressionNode::ASTStructExpressionNode(ASTStructStartNode* structStartNode, ASTStructEndNode* structEndNode) {
    _structStartNode = structStartNode;
    _structEndNode = structEndNode;
    _children.push_back(_structStartNode);
    _children.push_back(_structEndNode);
    _keyValuePairs = std::vector<ASTStructKeyValueNode*>();
    _commas = std::vector<ASTCommaNode*>();
}

ASTStructExpressionNode::ASTStructExpressionNode(ASTStructStartNode* structStartNode, std::vector<ASTStructKeyValueNode*> keyValuePairs, std::vector<ASTCommaNode*> commas, ASTStructEndNode* structEndNode) {
    _structStartNode = structStartNode;
    _structEndNode = structEndNode;
    _children.push_back(_structStartNode);
    _children.push_back(_structEndNode);
    _commas = commas;
    _keyValuePairs = keyValuePairs;
    for (auto keyValuePair : keyValuePairs) {
        _children.push_back(keyValuePair);
    }
}

std::vector<ASTStructKeyValueNode*> ASTStructExpressionNode::getKeyValuePairs() {
    return _keyValuePairs;
}

ASTStructKeyValueNode* ASTStructExpressionNode::getKeyValuePairAt(unsigned long index) {
    return _keyValuePairs.at(index);
}

ASTStructExpressionNode* ASTStructExpressionNode::addKeyValuePair(ASTStructKeyValueNode* keyValuePair) {
    _keyValuePairs.push_back(keyValuePair);
    _children.push_back(keyValuePair);
    return this;
}

ASTStructExpressionNode* ASTStructExpressionNode::addComma(ASTCommaNode* comma) {
    _commas.push_back(comma);
    return this;
}

StructTypeSignature* ASTStructExpressionNode::getTypeSignature() {
    return _typeSignature;
}

void ASTStructExpressionNode::setTypeSignature(StructTypeSignature* structTypeSignature) {
    _typeSignature = structTypeSignature;
}

Position* ASTStructExpressionNode::getStartPosition() {
    return _structStartNode->getStartPosition();
}

Position* ASTStructExpressionNode::getEndPosition() {
    return _structEndNode->getEndPosition();
}

ASTNodeType ASTStructExpressionNode::getNodeType() {
    return AST_STRUCT_EXPRESSION_NODE;
}

std::string ASTStructExpressionNode::toString() {
    return "STRUCT_EXPRESSION";
}

unsigned long ASTStructExpressionNode::size() {
    return _keyValuePairs.size();
}

bool ASTStructExpressionNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTStructExpressionNode*)other;
    auto otherNodeElements = otherNode->getKeyValuePairs();
    if (this->size() != otherNode->size()) {
        return false;
    }
    for (unsigned long i = 0; i < this->size(); i++) {
        if (!_keyValuePairs[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTStructExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto keyValuePair : _keyValuePairs) {
        keyValuePair->print();
    }
    Logger::log("----------");
}


std::string ASTStructExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_structStartNode);
    for (unsigned long i = 0; i < _keyValuePairs.size(); ++i) {
        sourceCodeBuilder.add(_keyValuePairs.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_structEndNode);
    return sourceCodeBuilder.build();
}