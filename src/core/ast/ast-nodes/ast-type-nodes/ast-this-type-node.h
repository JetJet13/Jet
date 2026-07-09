//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_THIS_TYPE_NODE_H
#define JETLANG_AST_THIS_TYPE_NODE_H

#include <string>
#include "ast-type-base-node.h"
#include "../ast-class-nodes/ast-this-node.h"

class ASTThisTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTThisNode> _this;
public:
    ASTThisTypeNode(std::shared_ptr<ASTThisNode> thisNode);
    std::shared_ptr<ASTThisNode> getThis();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_THIS_TYPE_NODE_H
