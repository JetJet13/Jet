//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-value-list-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumKeyValueListNode::ASTEnumKeyValueListNode() {
    _enumKeyValues = std::vector<ASTEnumKeyValueNode*>();
}

ASTEnumKeyValueListNode::ASTEnumKeyValueListNode(std::vector<ASTEnumKeyValueNode*> enumKeyValues) {
    _enumKeyValues = std::vector<ASTEnumKeyValueNode*>();
    for (auto enumKeyValue: enumKeyValues) {
        this->addEnumKeyValue(enumKeyValue);
    }
}

std::vector<ASTEnumKeyValueNode*> ASTEnumKeyValueListNode::getParameters() {
    return _enumKeyValues;
}

unsigned long ASTEnumKeyValueListNode::numParameters() {
    return _enumKeyValues.size();
}

ASTEnumKeyValueListNode* ASTEnumKeyValueListNode::addEnumKeyValue(ASTEnumKeyValueNode* enumKeyValue) {
    _enumKeyValues.push_back(enumKeyValue);
    _children.push_back(enumKeyValue);
    return this;
}

ASTNodeType ASTEnumKeyValueListNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_LIST_NODE;
}

std::string ASTEnumKeyValueListNode::toString() {
    return "ENUM_KEY_VALUE_LIST";
}

bool ASTEnumKeyValueListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTEnumKeyValueListNode*)other;
    auto otherNodeElements = otherNode->getParameters();
    if (this->numParameters() != otherNode->numParameters()) {
        return false;
    }
    for (int i = 0; i < this->numParameters(); i++) {
        if (!_enumKeyValues[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTEnumKeyValueListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto enumKeyValue : _enumKeyValues) {
        enumKeyValue->print();
    }
    Logger::log("----------");
}