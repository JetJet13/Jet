//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_THIS_TYPE_NODE_H
#define JETLANG_AST_THIS_TYPE_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "ast-type-node.h"
#include "../ast-class-nodes/ast-this-node.h"

class ASTThisTypeNode : public ASTTypeBaseNode {
private:
    ASTThisNode* _this;
public:
    ASTThisTypeNode(ASTThisNode* thisNode);
    ASTThisNode* getThis();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_THIS_TYPE_NODE_H
