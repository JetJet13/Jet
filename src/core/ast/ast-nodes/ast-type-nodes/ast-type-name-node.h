//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_AST_TYPE_NAME_NODE_H
#define JETLANG_AST_TYPE_NAME_NODE_H

#include "../ast-symbol-node.h"

class ASTTypeNameNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TYPE_NAME_NODE_H
