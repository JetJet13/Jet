//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H
#define JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/InstrTypes.h>
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "ir-unary-expression-node.h"

class IRUnaryNegateExpressionNode : public IRUnaryExpressionNode {
private:
    std::shared_ptr<ASTUnaryExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::shared_ptr<IRType> _type;
public:
    IRUnaryNegateExpressionNode(std::shared_ptr<ASTUnaryExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRType> type);
    std::shared_ptr<IRExpressionNode> getIRExpression();
    void markAsGlobal() override;
    llvm::Value* getValue() override;
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H
