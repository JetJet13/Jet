//
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTStructTypeNode::ASTStructTypeNode(ASTStructTypeStartNode* structTypeStartNode, ASTStructTypeEndNode* structTypeEndNode) {
    _structTypeStartNode = structTypeStartNode;
    _structTypeEndNode = structTypeEndNode;
    _commas = std::vector<ASTCommaNode*>();
    _keyValueTypes = std::vector<ASTStructTypeKeyValueNode*>();
}

ASTStructTypeNode::ASTStructTypeNode(ASTStructTypeStartNode* structTypeStartNode, std::vector<ASTStructTypeKeyValueNode*> keyValueTypes, std::vector<ASTCommaNode*> commas, ASTStructTypeEndNode* structTypeEndNode) {
    _structTypeStartNode = structTypeStartNode;
    _structTypeEndNode = structTypeEndNode;
    _commas = commas;
    _keyValueTypes = std::vector<ASTStructTypeKeyValueNode*>();
    for (auto keyValueType: keyValueTypes) {
        this->addKeyValueType(keyValueType);
    }
}

std::vector<ASTStructTypeKeyValueNode*> ASTStructTypeNode::getKeyValueTypes() {
    return _keyValueTypes;
}

unsigned long ASTStructTypeNode::numKeyValueTypes() {
    return _keyValueTypes.size();
}

ASTStructTypeNode* ASTStructTypeNode::addKeyValueType(ASTStructTypeKeyValueNode* keyValueType) {
    _keyValueTypes.push_back(keyValueType);
    _children.push_back(keyValueType);
    return this;
}

ASTStructTypeNode* ASTStructTypeNode::addComma(ASTCommaNode* comma) {
    _commas.push_back(comma);
    return this;
}

Position* ASTStructTypeNode::getStartPosition() {
    return _structTypeStartNode->getStartPosition();
}

Position* ASTStructTypeNode::getEndPosition() {
    return _structTypeEndNode->getEndPosition();
}

ASTNodeType ASTStructTypeNode::getNodeType() {
    return AST_STRUCT_TYPE_NODE;
}

std::string ASTStructTypeNode::toString() {
    return "STRUCT_TYPE";
}

bool ASTStructTypeNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTStructTypeNode*)other;
    auto otherNodeElements = otherNode->getKeyValueTypes();
    if (this->numKeyValueTypes() != otherNode->numKeyValueTypes()) {
        return false;
    }
    for (unsigned long i = 0; i < this->numKeyValueTypes(); i++) {
        if (!_keyValueTypes[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTStructTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto keyValueType : _keyValueTypes) {
        keyValueType->print();
    }
    Logger::log("----------");
}

std::string ASTStructTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_structTypeStartNode);
    for (unsigned long i = 0; i < _keyValueTypes.size(); ++i) {
        sourceCodeBuilder.add(_keyValueTypes.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_structTypeEndNode);
    return sourceCodeBuilder.build();
}