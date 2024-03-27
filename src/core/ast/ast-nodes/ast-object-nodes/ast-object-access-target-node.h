//
// Created by Johny Georges on 2024-03-27.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_TARGET_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_TARGET_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTObjectAccessTargetNode : public ASTNode {
private:
    ASTExpressionNode* _target;
public:
    ASTObjectAccessTargetNode(ASTExpressionNode* target);
    ASTExpressionNode* getTarget();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_TARGET_NODE_H
