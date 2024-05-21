//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_NODE_H
#define JETLANG_AST_NODE_H

#include <vector>
#include "../../lexeme/lexeme.h"
#include "../types/ast-node-type.h"
#include "../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"

class ASTNode {
protected:
    std::optional<ASTNode*> _parentNode;
    ASTNodeType _nodeType;
    unsigned int _priority = 1;
    std::string _id;
    std::vector<ASTNode*> _children = {};
public:
    std::string getId();
    ASTNode* setId(std::string id);
    std::optional<ASTNode*> getParentNode();
    void setParentNode(ASTNode* parentNode);
    virtual ASTNodeType getNodeType() = 0;
    virtual std::string toString() = 0;
    virtual bool isSameAs(ASTNode* other);
    virtual void print();
    virtual std::vector<ASTNode*> getChildren();
    virtual ASTNode* transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode);
    bool is(ASTNodeType astNodeType);
    bool isOneOf(std::vector<ASTNodeType> astNodeTypes);
    bool isSameNodeTypeAs(ASTNode* other);
    unsigned int getPriority();
    bool isHigherPriorityThan(ASTNode* other);
    bool isLowerPriorityThan(ASTNode* other);
};
#endif //JETLANG_AST_NODE_H
