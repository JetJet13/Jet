//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-value-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTEnumKeyValueListNode::ASTEnumKeyValueListNode(ASTEnumKeyValueListStartNode* enumKeyValueListStartNode, ASTEnumKeyValueListEndNode* enumKeyValueListEndNode) {
    _enumKeyValueListStartNode = enumKeyValueListStartNode;
    _enumKeyValueListEndNode = enumKeyValueListEndNode;
    _children.push_back(_enumKeyValueListStartNode);
    _children.push_back(_enumKeyValueListEndNode);
    _enumKeyValues = std::vector<ASTEnumKeyValueNode*>();
}

ASTEnumKeyValueListNode::ASTEnumKeyValueListNode(ASTEnumKeyValueListStartNode* enumKeyValueListStartNode, std::vector<ASTEnumKeyValueNode*> enumKeyValues, ASTEnumKeyValueListEndNode* enumKeyValueListEndNode) {
    _enumKeyValueListStartNode = enumKeyValueListStartNode;
    _enumKeyValueListEndNode = enumKeyValueListEndNode;
    _children.push_back(_enumKeyValueListStartNode);
    _children.push_back(_enumKeyValueListEndNode);
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

Position* ASTEnumKeyValueListNode::getStartPosition() {
    return _enumKeyValueListStartNode->getStartPosition();
}

Position* ASTEnumKeyValueListNode::getEndPosition() {
    return _enumKeyValueListEndNode->getEndPosition();
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

std::string ASTEnumKeyValueListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_enumKeyValueListStartNode);

    for (auto enumKeyValue : _enumKeyValues) {
        sourceCodeBuilder.addWithNewLine(enumKeyValue);
    }

    sourceCodeBuilder.addWithWhitespace(_enumKeyValueListEndNode);
    return sourceCodeBuilder.build();
}