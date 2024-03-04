//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_NODE_H
#define JETLANG_AST_NODE_H

#include <vector>
#include "../../lexeme/lexeme.h"
#include "../types/ast-node-type.h"

class ASTNode {
protected:
    std::optional<ASTNode*> _parentNode;
    ASTNodeType _nodeType;
public:
    void setParentNode(ASTNode* parentNode);
    virtual ASTNodeType getNodeType() = 0;
    virtual std::string toString() = 0;
    virtual bool isSameAs(ASTNode* other);
    virtual void print();
    virtual ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode);
    bool is(ASTNodeType astNodeType);
    bool isOneOf(std::vector<ASTNodeType> astNodeTypes);
};
#endif //JETLANG_AST_NODE_H
