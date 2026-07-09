//
// Created by Johny Georges on 2025-07-09.
//

#ifndef JETLANG_AST_VOID_TYPE_NODE_H
#define JETLANG_AST_VOID_TYPE_NODE_H

#include <string>
#include "ast-type-base-node.h"
#include "../ast-class-nodes/ast-this-node.h"
#include "../ast-void-node.h"

class ASTVoidTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTVoidNode> _void;
public:
    ASTVoidTypeNode(std::shared_ptr<ASTVoidNode> voidNode);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VOID_TYPE_NODE_H
