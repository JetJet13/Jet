//
// Created by Johny Georges on 2024-03-12.
//

#include "ast-struct-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTStructExpressionNode::ASTStructExpressionNode() {
    _keyValuePairs = std::vector<ASTStructKeyValueNode*>();
}

ASTStructExpressionNode::ASTStructExpressionNode(std::vector<ASTStructKeyValueNode*> keyValuePairs) {
    _keyValuePairs = keyValuePairs;
    for (auto keyValuePair : keyValuePairs) {
        _children.push_back(keyValuePair);
    }
}

std::vector<ASTStructKeyValueNode*> ASTStructExpressionNode::getKeyValuePairs() {
    return _keyValuePairs;
}

ASTStructExpressionNode* ASTStructExpressionNode::addKeyValuePair(ASTStructKeyValueNode* keyValuePair) {
    _keyValuePairs.push_back(keyValuePair);
    _children.push_back(keyValuePair);
    return this;
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

bool ASTStructExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTStructExpressionNode*)other;
    auto otherNodeElements = otherNode->getKeyValuePairs();
    if (this->size() != otherNode->size()) {
        return false;
    }
    for (int i = 0; i < this->size(); i++) {
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
    for (auto keyValuePair : _keyValuePairs) {
        sourceCodeBuilder.addWithNewLine(keyValuePair);
    }
    return sourceCodeBuilder.build();
}