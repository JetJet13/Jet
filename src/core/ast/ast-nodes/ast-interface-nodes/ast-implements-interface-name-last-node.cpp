//
// Created by Johny Georges on 2025-07-05.
//

#include "ast-implements-interface-name-last-node.h"

ASTImplementsInterfaceNameNode* ASTImplementsInterfaceNameLastNode::convertToInterfaceName() {
    return new ASTImplementsInterfaceNameNode(this->getLexeme());
}

ASTNodeType ASTImplementsInterfaceNameLastNode::getNodeType() {
    return AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE;
}

std::string ASTImplementsInterfaceNameLastNode::toString() {
    return "IMPLEMENTS_INTERFACE_NAME_LAST";
}

std::string ASTImplementsInterfaceNameLastNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}