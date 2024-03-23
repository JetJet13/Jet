//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-key-value-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumKeyValueNode::ASTEnumKeyValueNode(ASTEnumKeyNode* key, ASTLiteralNode* value) {
    _key = key;
    _value = value;
}

ASTEnumKeyNode* ASTEnumKeyValueNode::getKey() {
    return _key;
}

ASTLiteralNode* ASTEnumKeyValueNode::getValue() {
    return _value;
}

ASTNodeType ASTEnumKeyValueNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_NODE;
}

std::string ASTEnumKeyValueNode::toString() {
    return "ENUM_KEY_VALUE";
}

bool ASTEnumKeyValueNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTEnumKeyValueNode*)other;
    return _key->isSameAs(otherNode->getKey()) && _value->isSameAs(otherNode->getValue());
}

void ASTEnumKeyValueNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _key->print();
    _value->print();
    Logger::log("----------");
}