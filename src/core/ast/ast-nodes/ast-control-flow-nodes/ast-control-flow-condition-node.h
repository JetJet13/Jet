//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_CONTROL_FLOW_CONDITION_NODE_H
#define JETLANG_AST_CONTROL_FLOW_CONDITION_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTControlFlowConditionNode : public ASTNode {
private:
    std::shared_ptr<ASTExpressionNode> _condition;
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    ASTControlFlowConditionNode(std::shared_ptr<ASTExpressionNode> condition);
    std::shared_ptr<ASTExpressionNode> getCondition();
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CONTROL_FLOW_CONDITION_NODE_H
