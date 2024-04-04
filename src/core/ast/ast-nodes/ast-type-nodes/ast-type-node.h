//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_TYPE_NODE_H
#define JETLANG_AST_TYPE_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTTypeNode : public ASTNode {
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_TYPE_NODE_H
