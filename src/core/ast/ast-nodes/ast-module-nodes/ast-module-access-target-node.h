//
// Created by Johny Georges on 2024-11-05.
//

#ifndef JETLANG_AST_MODULE_ACCESS_TARGET_NODE_H
#define JETLANG_AST_MODULE_ACCESS_TARGET_NODE_H

#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTModuleAccessTargetNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _target;
public:
    ASTModuleAccessTargetNode(ASTIdentifierExpressionNode* target);
    ASTIdentifierExpressionNode* getTarget();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_TARGET_NODE_H
