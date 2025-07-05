//
// Created by Johny Georges on 2025-07-05.
//

#ifndef JETLANG_AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE_H
#define JETLANG_AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE_H

#include "../ast-symbol-node.h"
#include "ast-implements-interface-name-node.h"

class ASTImplementsInterfaceNameLastNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTImplementsInterfaceNameNode* convertToInterfaceName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    std::string toSourceCode() override;
};
#endif //JETLANG_AST_IMPLEMENTS_INTERFACE_NAME_LAST_NODE_H
