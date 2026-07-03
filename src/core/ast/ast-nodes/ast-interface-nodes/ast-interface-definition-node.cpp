//
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTInterfaceDefinitionNode::ASTInterfaceDefinitionNode(ASTInterfaceNode* interfaceKeyword, ASTInterfaceNameNode* name) {
    _interfaceKeyword = interfaceKeyword;
    _name = name;
    _children.push_back(_interfaceKeyword);
    _children.push_back(_name);
}


ASTInterfaceNameNode* ASTInterfaceDefinitionNode::getName() {
    return _name;
}

Position* ASTInterfaceDefinitionNode::getStartPosition() {
    return _interfaceKeyword->getStartPosition();
}

Position* ASTInterfaceDefinitionNode::getEndPosition() {
    return _name->getEndPosition();
}

ASTNodeType ASTInterfaceDefinitionNode::getNodeType() {
    return AST_INTERFACE_DEFINITION_NODE;
}

std::string ASTInterfaceDefinitionNode::toString() {
    return "INTERFACE_DEFINITION";
}

bool ASTInterfaceDefinitionNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTInterfaceDefinitionNode*)other;

    return  this->getName()->isSameAs(otherNode->getName());
}

void ASTInterfaceDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    Logger::log("----------");
}

std::string ASTInterfaceDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_interfaceKeyword);
    sourceCodeBuilder.add(_name);
    return sourceCodeBuilder.build();
}