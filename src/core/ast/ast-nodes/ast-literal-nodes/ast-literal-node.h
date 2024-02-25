//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_LITERAL_NODE_H
#define JETLANG_AST_LITERAL_NODE_H

#include "../../types/ast-node-type.h"
#include "../ast-node.h"

class ASTLiteralNode : public ASTNode {
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_LITERAL_NODE_H
