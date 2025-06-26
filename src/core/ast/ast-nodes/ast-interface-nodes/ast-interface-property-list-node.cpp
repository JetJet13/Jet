//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-property-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTInterfacePropertyListNode::ASTInterfacePropertyListNode(ASTInterfaceStartNode* startNode, ASTInterfaceEndNode* endNode) {
    _startNode = startNode;
    _endNode = endNode;
    _children.push_back(_startNode);
    _children.push_back(_endNode);
    _properties = std::vector<ASTInterfacePropertyNode*>();
}

ASTInterfacePropertyListNode::ASTInterfacePropertyListNode(ASTInterfaceStartNode* startNode, std::vector<ASTInterfacePropertyNode*> properties, ASTInterfaceEndNode* endNode) {
    _startNode = startNode;
    _endNode = endNode;
    _children.push_back(_startNode);
    _children.push_back(_endNode);
    _properties = std::vector<ASTInterfacePropertyNode*>();
    for (auto property: properties) {
        this->addProperty(property);
    }
}

std::vector<ASTInterfacePropertyNode*> ASTInterfacePropertyListNode::getParameters() {
    return _properties;
}

unsigned long ASTInterfacePropertyListNode::numProperties() {
    return _properties.size();
}

ASTInterfacePropertyListNode* ASTInterfacePropertyListNode::addProperty(ASTInterfacePropertyNode* property) {
    _properties.push_back(property);
    _children.push_back(property);
    return this;
}

Position* ASTInterfacePropertyListNode::getStartPosition() {
    return _startNode->getStartPosition();
}

Position* ASTInterfacePropertyListNode::getEndPosition() {
    return _endNode->getEndPosition();
}

ASTNodeType ASTInterfacePropertyListNode::getNodeType() {
    return AST_INTERFACE_PROPERTY_LIST_NODE;
}

std::string ASTInterfacePropertyListNode::toString() {
    return "INTERFACE_PROPERTY_LIST";
}

bool ASTInterfacePropertyListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTInterfacePropertyListNode*)other;
    auto otherNodeElements = otherNode->getParameters();
    if (this->numProperties() != otherNode->numProperties()) {
        return false;
    }
    for (int i = 0; i < this->numProperties(); i++) {
        if (!_properties[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTInterfacePropertyListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto enumKeyValue : _properties) {
        enumKeyValue->print();
    }
    Logger::log("----------");
}

std::string ASTInterfacePropertyListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_startNode);

    for (auto enumKeyValue : _properties) {
        sourceCodeBuilder.addWithNewLine(enumKeyValue);
    }

    sourceCodeBuilder.addWithWhitespace(_endNode);
    return sourceCodeBuilder.build();
}