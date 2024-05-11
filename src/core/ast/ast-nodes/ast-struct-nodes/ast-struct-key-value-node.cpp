//
// Created by Johny Georges on 2024-03-12.
//

#include "ast-struct-key-value-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTStructKeyValueNode::ASTStructKeyValueNode(ASTIdentifierExpressionNode* key, ASTExpressionNode* value) {
    _key = key;
    _value = value;
    _children.push_back(_key);
    _children.push_back(_value);
}

ASTIdentifierExpressionNode* ASTStructKeyValueNode::getKey() {
    return _key;
}

ASTExpressionNode* ASTStructKeyValueNode::getValue() {
    return _value;
}

ASTNodeType ASTStructKeyValueNode::getNodeType() {
    return AST_STRUCT_KEY_VALUE_NODE;
}

std::string ASTStructKeyValueNode::toString() {
    return "STRUCT_KEY_VALUE";
}

bool ASTStructKeyValueNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTStructKeyValueNode*)other;
    return _key->isSameAs(otherNode->getKey()) && _value->isSameAs(otherNode->getValue());
}

void ASTStructKeyValueNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _key->print();
    _value->print();
    Logger::log("----------");
}