//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-type-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTInterfaceTypeDeclarationNode::ASTInterfaceTypeDeclarationNode(std::shared_ptr<ASTInterfaceDefinitionNode> interfaceDefinition, std::shared_ptr<ASTInterfacePropertyListNode> propertyList, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword) {
    _interfaceDefinition = interfaceDefinition;
    _propertyList = propertyList;
    _exportKeyword = exportKeyword;
    _children.push_back(_interfaceDefinition);
    _children.push_back(_propertyList);
    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }
}

std::shared_ptr<ASTInterfacePropertyListNode> ASTInterfaceTypeDeclarationNode::getProperties() {
    return _propertyList;
}

std::shared_ptr<ASTInterfaceNameNode> ASTInterfaceTypeDeclarationNode::getName() {
    return _interfaceDefinition->getName();
}

unsigned long ASTInterfaceTypeDeclarationNode::numProperties() {
    return _propertyList->numProperties();
}

bool ASTInterfaceTypeDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

void ASTInterfaceTypeDeclarationNode::setTypeSignature(std::shared_ptr<InterfaceTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<InterfaceTypeSignature> ASTInterfaceTypeDeclarationNode::getInterfaceTypeSignature() {
    return std::dynamic_pointer_cast<InterfaceTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTInterfaceTypeDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTInterfaceTypeDeclarationNode::getStartPosition() {
    return _interfaceDefinition->getStartPosition();
}

std::shared_ptr<Position> ASTInterfaceTypeDeclarationNode::getEndPosition() {
    return _propertyList->getEndPosition();
}

ASTNodeType ASTInterfaceTypeDeclarationNode::getNodeType() {
    return AST_INTERFACE_TYPE_DECLARATION_NODE;
}

std::string ASTInterfaceTypeDeclarationNode::toString() {
    return "INTERFACE_TYPE_DECLARATION";
}

bool ASTInterfaceTypeDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTInterfaceTypeDeclarationNode>(other);
    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getProperties()->isSameAs(otherNode->getProperties());
}

void ASTInterfaceTypeDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_exportKeyword) {
        _exportKeyword.value()->print();
    }
    _interfaceDefinition->print();
    _propertyList->print();
    Logger::log("----------");
}

std::string ASTInterfaceTypeDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    if (_exportKeyword) {
        sourceCodeBuilder.add(_exportKeyword.value())->add(_interfaceDefinition);
    } else {
        sourceCodeBuilder.add(_interfaceDefinition);
    }
    sourceCodeBuilder.add(_propertyList);
    return sourceCodeBuilder.build();
}