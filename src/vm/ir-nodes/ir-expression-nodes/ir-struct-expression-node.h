//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_STRUCT_EXPRESSION_NODE_H
#define JETLANG_IR_STRUCT_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-struct-ref-type.h"

class IRStructExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTStructExpressionNode> _node;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRInstructionNode> _irArc;
    std::vector<std::shared_ptr<IRExpressionNode>> _irValues;
    std::shared_ptr<IRStructRefType> _type;
public:
    IRStructExpressionNode(std::shared_ptr<ASTStructExpressionNode> astNode, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> irArc, std::shared_ptr<IRStructRefType> type, std::vector<std::shared_ptr<IRExpressionNode>> irValues);
    void markAsGlobal() override;
    std::shared_ptr<IRStructRefType> getIRStructRefType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getArc() override;
    unsigned long size();
    llvm::Value* getValue() override;
    std::shared_ptr<IRInstructionNode> getIRValue();
    std::vector<std::shared_ptr<IRExpressionNode>>* getValues();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRUCT_EXPRESSION_NODE_H
