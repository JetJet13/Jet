//
// Created by Johny Georges on 2024-03-27.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_TARGET_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_TARGET_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTObjectAccessTargetNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _target;
public:
    ASTObjectAccessTargetNode(ASTIdentifierExpressionNode* target);
    ASTIdentifierExpressionNode* getTarget();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_TARGET_NODE_H
