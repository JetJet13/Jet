//
// Created by Johny Georges on 2025-07-05.
//

#include "ast-implements-interface-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImplementsInterfaceListNode::ASTImplementsInterfaceListNode(ASTImplementsNode* implementsKeyword) {
    _implements = implementsKeyword;
    _children.push_back(_implements);
    _commas = std::vector<ASTCommaNode*>();
    _interfaceNames = std::vector<ASTImplementsInterfaceNameNode*>();
}

ASTImplementsInterfaceListNode::ASTImplementsInterfaceListNode(ASTImplementsNode* implementsKeyword, std::vector<ASTImplementsInterfaceNameNode*> interfaceNames, std::vector<ASTCommaNode*> commas) {
    _implements = implementsKeyword;
    _children.push_back(_implements);
    _commas = commas;
    _interfaceNames = std::vector<ASTImplementsInterfaceNameNode*>();
    for (auto interfaceName: interfaceNames) {
        this->addInterface(interfaceName);
    }
}

std::vector<ASTImplementsInterfaceNameNode*> ASTImplementsInterfaceListNode::getInterfaceNames() {
    return _interfaceNames;
}

unsigned long ASTImplementsInterfaceListNode::numInterfaces() {
    return _interfaceNames.size();
}

ASTImplementsInterfaceListNode* ASTImplementsInterfaceListNode::addInterface(ASTImplementsInterfaceNameNode* interfaceName) {
    _interfaceNames.push_back(interfaceName);
    _children.push_back(interfaceName);
    return this;
}

ASTImplementsInterfaceListNode* ASTImplementsInterfaceListNode::addComma(ASTCommaNode* comma) {
    _commas.push_back(comma);
    return this;
}

Position* ASTImplementsInterfaceListNode::getStartPosition() {
    return _implements->getStartPosition();
}

Position* ASTImplementsInterfaceListNode::getEndPosition() {
    return _interfaceNames[_interfaceNames.size() - 1]->getEndPosition();
}

ASTNodeType ASTImplementsInterfaceListNode::getNodeType() {
    return AST_IMPLEMENTS_INTERFACE_LIST_NODE;
}

std::string ASTImplementsInterfaceListNode::toString() {
    return "IMPLEMENTS_INTERFACE_LIST";
}

bool ASTImplementsInterfaceListNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImplementsInterfaceListNode*)other;
    auto otherNodeElements = otherNode->getInterfaceNames();
    if (this->numInterfaces() != otherNode->numInterfaces()) {
        return false;
    }
    for (unsigned long i = 0; i < this->numInterfaces(); i++) {
        if (!_interfaceNames[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }
    return true;
}

void ASTImplementsInterfaceListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto interfaceName : _interfaceNames) {
        interfaceName->print();
    }
    Logger::log("----------");
}

std::string ASTImplementsInterfaceListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_implements);

    for (unsigned long i = 0; i < _interfaceNames.size(); ++i) {
        sourceCodeBuilder.add(_interfaceNames.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }

    return sourceCodeBuilder.build();
}