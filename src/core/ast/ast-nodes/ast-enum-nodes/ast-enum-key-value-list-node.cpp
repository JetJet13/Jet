//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-value-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTEnumKeyValueListNode::ASTEnumKeyValueListNode(std::shared_ptr<ASTEnumKeyValueListStartNode> enumKeyValueListStartNode, std::shared_ptr<ASTEnumKeyValueListEndNode> enumKeyValueListEndNode) {
    _enumKeyValueListStartNode = enumKeyValueListStartNode;
    _enumKeyValueListEndNode = enumKeyValueListEndNode;
    _children.push_back(_enumKeyValueListStartNode);
    _children.push_back(_enumKeyValueListEndNode);
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _enumKeyValues = std::vector<std::shared_ptr<ASTEnumKeyValueNode>>();
}

ASTEnumKeyValueListNode::ASTEnumKeyValueListNode(std::shared_ptr<ASTEnumKeyValueListStartNode> enumKeyValueListStartNode, std::vector<std::shared_ptr<ASTEnumKeyValueNode>> enumKeyValues, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTEnumKeyValueListEndNode> enumKeyValueListEndNode) {
    _enumKeyValueListStartNode = enumKeyValueListStartNode;
    _enumKeyValueListEndNode = enumKeyValueListEndNode;
    _children.push_back(_enumKeyValueListStartNode);
    _children.push_back(_enumKeyValueListEndNode);
    _commas = commas;
    _enumKeyValues = std::vector<std::shared_ptr<ASTEnumKeyValueNode>>();
    for (auto enumKeyValue: enumKeyValues) {
        this->addEnumKeyValue(enumKeyValue);
    }
}

std::vector<std::shared_ptr<ASTEnumKeyValueNode>> ASTEnumKeyValueListNode::getParameters() {
    return _enumKeyValues;
}

uint64_t ASTEnumKeyValueListNode::numParameters() {
    return _enumKeyValues.size();
}

std::shared_ptr<ASTEnumKeyValueListNode> ASTEnumKeyValueListNode::addEnumKeyValue(std::shared_ptr<ASTEnumKeyValueNode> enumKeyValue) {
    _enumKeyValues.push_back(enumKeyValue);
    _children.push_back(enumKeyValue);
    return std::dynamic_pointer_cast<ASTEnumKeyValueListNode>(shared_from_this());
}

std::shared_ptr<ASTEnumKeyValueListNode> ASTEnumKeyValueListNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTEnumKeyValueListNode>(shared_from_this());
}

std::shared_ptr<Position> ASTEnumKeyValueListNode::getStartPosition() {
    return _enumKeyValueListStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTEnumKeyValueListNode::getEndPosition() {
    return _enumKeyValueListEndNode->getEndPosition();
}

ASTNodeType ASTEnumKeyValueListNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_LIST_NODE;
}

std::string ASTEnumKeyValueListNode::toString() {
    return "ENUM_KEY_VALUE_LIST";
}

bool ASTEnumKeyValueListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTEnumKeyValueListNode>(other);
    auto otherNodeElements = otherNode->getParameters();
    if (this->numParameters() != otherNode->numParameters()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numParameters(); i++) {
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

    for (uint64_t i = 0; i < _enumKeyValues.size(); ++i) {
        sourceCodeBuilder.add(_enumKeyValues.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }

    sourceCodeBuilder.add(_enumKeyValueListEndNode);
    return sourceCodeBuilder.build();
}