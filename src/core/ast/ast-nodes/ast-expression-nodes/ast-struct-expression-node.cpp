//
// Created by Johny Georges on 2024-03-12.
//

#include "ast-struct-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTStructExpressionNode::ASTStructExpressionNode(std::shared_ptr<ASTStructStartNode> structStartNode, std::shared_ptr<ASTStructEndNode> structEndNode) {
    _structStartNode = structStartNode;
    _structEndNode = structEndNode;
    _children.push_back(_structStartNode);
    _children.push_back(_structEndNode);
    _keyValuePairs = std::vector<std::shared_ptr<ASTStructKeyValueNode>>();
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
}

ASTStructExpressionNode::ASTStructExpressionNode(std::shared_ptr<ASTStructStartNode> structStartNode, std::vector<std::shared_ptr<ASTStructKeyValueNode>> keyValuePairs, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTStructEndNode> structEndNode) {
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

std::vector<std::shared_ptr<ASTStructKeyValueNode>> ASTStructExpressionNode::getKeyValuePairs() {
    return _keyValuePairs;
}

std::shared_ptr<ASTStructKeyValueNode> ASTStructExpressionNode::getKeyValuePairAt(unsigned long index) {
    return _keyValuePairs.at(index);
}

std::shared_ptr<ASTStructExpressionNode> ASTStructExpressionNode::addKeyValuePair(std::shared_ptr<ASTStructKeyValueNode> keyValuePair) {
    _keyValuePairs.push_back(keyValuePair);
    _children.push_back(keyValuePair);
    return std::dynamic_pointer_cast<ASTStructExpressionNode>(shared_from_this());
}

std::shared_ptr<ASTStructExpressionNode> ASTStructExpressionNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTStructExpressionNode>(shared_from_this());
}

std::shared_ptr<TypeSignature> ASTStructExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<StructTypeSignature> ASTStructExpressionNode::getStructTypeSignature() {
    return std::dynamic_pointer_cast<StructTypeSignature>(_typeSignature);
}

void ASTStructExpressionNode::setTypeSignature(std::shared_ptr<StructTypeSignature> structTypeSignature) {
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

bool ASTStructExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTStructExpressionNode>(other);
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