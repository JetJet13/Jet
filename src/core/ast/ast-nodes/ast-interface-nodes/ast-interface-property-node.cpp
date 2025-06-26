//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-property-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTInterfacePropertyNode::ASTInterfacePropertyNode(ASTIdentifierExpressionNode* identifier, ASTTypeColonNode* colon, ASTTypeNode* type) {
    _identifier = identifier;
    _colon = colon;
    _type = type;
    _children.push_back(_identifier);
    _children.push_back(_colon);
    _children.push_back(_type);
}

ASTIdentifierExpressionNode* ASTInterfacePropertyNode::getIdentifier() {
    return _identifier;
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
    return _identifier->getStartPosition();
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
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier()) &&
           this->getType()->isSameAs(otherNode->getType());
}

void ASTInterfacePropertyNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    _type->print();
    Logger::log("----------");
}

std::string ASTInterfacePropertyNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_identifier)
    ->add(_colon)
    ->addWithWhitespace(_type);
    return sourceCodeBuilder.build();
}