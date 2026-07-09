//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_NULL_NODE_H
#define JETLANG_AST_NULL_NODE_H

#include "ast-node.h"

class ASTNullNode : public ASTNode {
public:
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
};

#endif //JETLANG_AST_NULL_NODE_H
