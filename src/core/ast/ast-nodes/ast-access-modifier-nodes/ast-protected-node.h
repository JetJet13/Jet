//
// Created by Johny Georges on 2024-04-18.
//

#ifndef JETLANG_AST_PROTECTED_NODE_H
#define JETLANG_AST_PROTECTED_NODE_H

#include "ast-access-modifier-node.h"

class ASTProtectedNode : public ASTAccessModifierNode {
    using ASTAccessModifierNode::ASTAccessModifierNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_PROTECTED_NODE_H
