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
    llvm::UnaryOperator* _irValue;
    IRExpressionNode* _irExpression;
    IRType* _type;
    IRInstructionNode* _sourceAllocation;
public:
    IRUnaryNegateExpressionNode(ASTUnaryExpressionNode* node, llvm::UnaryOperator* irValue, IRExpressionNode* irExpression, IRType* type, IRInstructionNode* sourceAllocation);
    llvm::Value *insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) override;
    llvm::UnaryOperator* getValue() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    IRType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H
