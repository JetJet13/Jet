//
// Created by Johny Georges on 2026-03-14.
//

#include "ast-tuple-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTTupleTypeNode::ASTTupleTypeNode(ASTTupleTypeStartNode* tupleTypeStartNode, ASTTupleTypeEndNode* tupleTypeEndNode) {
    _tupleTypeStartNode = tupleTypeStartNode;
    _tupleTypeEndNode = tupleTypeEndNode;
    _commas = std::vector<ASTCommaNode*>();
    _types = std::vector<ASTTypeNode*>();
}

ASTTupleTypeNode::ASTTupleTypeNode(ASTTupleTypeStartNode* tupleTypeStartNode, std::vector<ASTTypeNode*> valueTypes, std::vector<ASTCommaNode*> commas, ASTTupleTypeEndNode* tupleTypeEndNode) {
    _tupleTypeStartNode = tupleTypeStartNode;
    _tupleTypeEndNode = tupleTypeEndNode;
    _commas = commas;
    _types = std::vector<ASTTypeNode*>();
    for (auto keyValueType: valueTypes) {
        this->addValueType(keyValueType);
    }
}

std::vector<ASTTypeNode*> ASTTupleTypeNode::getValueTypes() {
    return _types;
}

unsigned long ASTTupleTypeNode::numValueTypes() {
    return _types.size();
}

ASTTupleTypeNode* ASTTupleTypeNode::addValueType(ASTTypeNode* type) {
    _types.push_back(type);
    _children.push_back(type);
    return this;
}

ASTTupleTypeNode* ASTTupleTypeNode::addComma(ASTCommaNode* comma) {
    _commas.push_back(comma);
    return this;
}

Position* ASTTupleTypeNode::getStartPosition() {
    return _tupleTypeStartNode->getStartPosition();
}

Position* ASTTupleTypeNode::getEndPosition() {
    return _tupleTypeEndNode->getEndPosition();
}

ASTNodeType ASTTupleTypeNode::getNodeType() {
    return AST_TUPLE_TYPE_NODE;
}

std::string ASTTupleTypeNode::toString() {
    return "TUPLE_TYPE";
}

bool ASTTupleTypeNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleTypeNode*)other;
    auto otherNodeElements = otherNode->getValueTypes();
    if (this->numValueTypes() != otherNode->numValueTypes()) {
        return false;
    }
    for (unsigned long i = 0; i < this->numValueTypes(); i++) {
        if (!_types[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTTupleTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto valueType : _types) {
        valueType->print();
    }
    Logger::log("----------");
}

std::string ASTTupleTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleTypeStartNode);
    for (unsigned long i = 0; i < _types.size(); ++i) {
        sourceCodeBuilder.add(_types.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_tupleTypeEndNode);
    return sourceCodeBuilder.build();
}