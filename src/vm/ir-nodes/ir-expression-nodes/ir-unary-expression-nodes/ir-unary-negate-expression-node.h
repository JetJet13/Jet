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
    ASTUnaryExpressionNode* _node;
    IRExpressionNode* _irExpression;
    IRType* _type;
public:
    IRUnaryNegateExpressionNode(ASTUnaryExpressionNode* node, IRExpressionNode* irExpression, IRType* type);
    IRExpressionNode* getIRExpression();
    void markAsGlobal() override;
    llvm::Value* getValue() override;
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H
