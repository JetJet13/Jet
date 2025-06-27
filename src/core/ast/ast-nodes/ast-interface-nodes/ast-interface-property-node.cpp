//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-property-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTInterfacePropertyNode::ASTInterfacePropertyNode(ASTInterfacePropertyNameNode* name, ASTInterfaceColonNode* colon, ASTTypeNode* type) {
    _name = name;
    _colon = colon;
    _type = type;
    _children.push_back(_name);
    _children.push_back(_colon);
    _children.push_back(_type);
}

ASTInterfacePropertyNameNode* ASTInterfacePropertyNode::getName() {
    return _name;
}

ASTTypeNode* ASTInterfacePropertyNode::getType() {
    return _type;
}

void ASTInterfacePropertyNode::setTypeSignature(InterfacePropertyTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

InterfacePropertyTypeSignature* ASTInterfacePropertyNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTInterfacePropertyNode::getStartPosition() {
    return _name->getStartPosition();
}

Position* ASTInterfacePropertyNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTInterfacePropertyNode::getNodeType() {
    return AST_INTERFACE_PROPERTY_NODE;
}

std::string ASTInterfacePropertyNode::toString() {
    return "INTERFACE_PROPERTY";
}

bool ASTInterfacePropertyNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTInterfacePropertyNode*)other;
    return this->getName()->isSameAs(otherNode->getName()) &&
           this->getType()->isSameAs(otherNode->getType());
}

void ASTInterfacePropertyNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _type->print();
    Logger::log("----------");
}

std::string ASTInterfacePropertyNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_name)
    ->add(_colon)
    ->addWithWhitespace(_type);
    return sourceCodeBuilder.build();
}