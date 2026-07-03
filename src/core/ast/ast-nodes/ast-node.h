//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_NODE_H
#define JETLANG_AST_NODE_H

#include <vector>
#include "../../lexeme/lexeme.h"
#include "../types/ast-node-type.h"
#include "../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"
#include "../../type-signature/type-signature.h"

class ASTNode {
protected:
    std::optional<ASTNode*> _parentNode;
    ASTNodeType _nodeType;
    unsigned int _priority = 1;
    std::string _id;
    std::vector<ASTNode*> _children = {};
    bool _isGlobal = false;
    bool _isGrouped = false;
public:
    std::string getId();
    ASTNode* setId(std::string id);
    std::optional<ASTNode*> getParentNode();
    void setParentNode(ASTNode* parentNode);
    void markAsGlobal();
    void markAsGrouped();
    virtual ASTNodeType getNodeType() = 0;
    virtual std::string toString() = 0;
    virtual Position* getStartPosition();
    virtual Position* getEndPosition();
    virtual std::string getLineColumn();
    virtual bool isSameAs(ASTNode* other);
    virtual bool isExpression();
    virtual bool isScopedBlockNode();
    virtual void print();
    virtual std::string toSourceCode();
    virtual TypeSignature* getTypeSignature();
    virtual std::vector<ASTNode*> getChildren();
    virtual ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode);
    virtual bool isExportable();
    virtual bool isGlobal();
    bool isGrouped();
    bool is(ASTNodeType astNodeType);
    bool isOneOf(std::vector<ASTNodeType> astNodeTypes);
    bool isSameNodeTypeAs(ASTNode* other);
    unsigned int getPriority();
    bool isHigherPriorityThan(ASTNode* other);
    bool isLowerPriorityThan(ASTNode* other);
};
#endif //JETLANG_AST_NODE_H
