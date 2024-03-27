//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <string>
#include "ast-expression-node.h"
#include "ast-identifier-expression-node.h"
#include "../ast-object-nodes/ast-object-access-source-node.h"
#include "../ast-object-nodes/ast-object-access-target-node.h"

class ASTObjectAccessExpressionNode : public ASTExpressionNode {
private:
    ASTObjectAccessSourceNode* _source;
    ASTObjectAccessTargetNode* _target;
public:
    ASTObjectAccessExpressionNode(ASTObjectAccessSourceNode* source, ASTObjectAccessTargetNode* property);
    ASTObjectAccessSourceNode* getSource();
    ASTObjectAccessTargetNode* getTarget();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
