//
// Created by Johny Georges on 2026-05-30.
//

#ifndef JETLANG_AST_MODULE_TYPE_TARGET_NODE_H
#define JETLANG_AST_MODULE_TYPE_TARGET_NODE_H

#include "../../ast-symbol-node.h"

class ASTModuleTypeTargetNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_MODULE_TYPE_TARGET_NODE_H
