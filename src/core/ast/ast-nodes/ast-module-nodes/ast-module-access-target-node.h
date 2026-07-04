//
// Created by Johny Georges on 2024-11-05.
//

#ifndef JETLANG_AST_MODULE_ACCESS_TARGET_NODE_H
#define JETLANG_AST_MODULE_ACCESS_TARGET_NODE_H

#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTModuleAccessTargetNode : public ASTNode {
private:
    std::shared_ptr<ASTIdentifierExpressionNode> _target;
public:
    ASTModuleAccessTargetNode(std::shared_ptr<ASTIdentifierExpressionNode> target);
    std::shared_ptr<ASTIdentifierExpressionNode> getTarget();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_TARGET_NODE_H
