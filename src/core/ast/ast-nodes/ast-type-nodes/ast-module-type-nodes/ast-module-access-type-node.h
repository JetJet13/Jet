//
// Created by Johny Georges on 2026-05-30.
//

#ifndef JETLANG_AST_MODULE_ACCESS_TYPE_NODE_H
#define JETLANG_AST_MODULE_ACCESS_TYPE_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"
#include "../../ast-symbol-node.h"

class ASTModuleAccessTypeNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_TYPE_NODE_H
