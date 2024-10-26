//
// Created by Johny Georges on 2024-10-24.
//

#ifndef JETLANG_AST_EXPORT_NODE_H
#define JETLANG_AST_EXPORT_NODE_H

#include "ast-symbol-node.h"

class ASTExportNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_EXPORT_NODE_H
