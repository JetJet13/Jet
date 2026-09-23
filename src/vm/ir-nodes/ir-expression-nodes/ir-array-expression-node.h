//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_ARRAY_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-array-pointer-type.h"
#include "ir-expression-node.h"


class IRArrayExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTArrayExpressionNode> _node;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRInstructionNode> _arrayPointerSourceAllocation;
    std::vector<std::shared_ptr<IRExpressionNode>> _irValues;
    std::shared_ptr<IRArrayPointerType> _type;
public:
    IRArrayExpressionNode(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> arrayPointerSourceAllocation, std::vector<std::shared_ptr<IRExpressionNode>> irValues, std::shared_ptr<IRArrayPointerType> type);
    void markAsGlobal() override;
    llvm::Value* getValue() override;
    std::vector<std::shared_ptr<IRExpressionNode>>* getValues();
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::shared_ptr<IRInstructionNode> getSourceAggregateAllocation();
    std::shared_ptr<IRInstructionNode> getAggregatePointerAllocation();
    std::shared_ptr<IRArrayPointerType> getIRArrayPointerType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    uint64_t size();
    llvm::Type* getTypeAtIndex(uint64_t index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_ARRAY_EXPRESSION_NODE_H
