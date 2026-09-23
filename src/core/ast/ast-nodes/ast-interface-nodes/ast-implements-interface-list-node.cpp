//
// Created by Johny Georges on 2025-07-05.
//

#include "ast-implements-interface-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImplementsInterfaceListNode::ASTImplementsInterfaceListNode(std::shared_ptr<ASTImplementsNode> implementsKeyword) {
    _implements = implementsKeyword;
    _children.push_back(_implements);
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _interfaceNames = std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>>();
}

ASTImplementsInterfaceListNode::ASTImplementsInterfaceListNode(std::shared_ptr<ASTImplementsNode> implementsKeyword, std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>> interfaceNames, std::vector<std::shared_ptr<ASTCommaNode>> commas) {
    _implements = implementsKeyword;
    _children.push_back(_implements);
    _commas = commas;
    _interfaceNames = std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>>();
    for (auto interfaceName: interfaceNames) {
        this->addInterface(interfaceName);
    }
}

std::vector<std::shared_ptr<ASTImplementsInterfaceNameNode>> ASTImplementsInterfaceListNode::getInterfaceNames() {
    return _interfaceNames;
}

uint64_t ASTImplementsInterfaceListNode::numInterfaces() {
    return _interfaceNames.size();
}

std::shared_ptr<ASTImplementsInterfaceListNode> ASTImplementsInterfaceListNode::addInterface(std::shared_ptr<ASTImplementsInterfaceNameNode> interfaceName) {
    _interfaceNames.push_back(interfaceName);
    _children.push_back(interfaceName);
    return std::dynamic_pointer_cast<ASTImplementsInterfaceListNode>(shared_from_this());
}

std::shared_ptr<ASTImplementsInterfaceListNode> ASTImplementsInterfaceListNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTImplementsInterfaceListNode>(shared_from_this());
}

std::shared_ptr<Position> ASTImplementsInterfaceListNode::getStartPosition() {
    return _implements->getStartPosition();
}

std::shared_ptr<Position> ASTImplementsInterfaceListNode::getEndPosition() {
    return _interfaceNames[_interfaceNames.size() - 1]->getEndPosition();
}

ASTNodeType ASTImplementsInterfaceListNode::getNodeType() {
    return AST_IMPLEMENTS_INTERFACE_LIST_NODE;
}

std::string ASTImplementsInterfaceListNode::toString() {
    return "IMPLEMENTS_INTERFACE_LIST";
}

bool ASTImplementsInterfaceListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImplementsInterfaceListNode>(other);
    auto otherNodeElements = otherNode->getInterfaceNames();
    if (this->numInterfaces() != otherNode->numInterfaces()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numInterfaces(); i++) {
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

    for (uint64_t i = 0; i < _interfaceNames.size(); ++i) {
        sourceCodeBuilder.add(_interfaceNames.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }

    return sourceCodeBuilder.build();
}