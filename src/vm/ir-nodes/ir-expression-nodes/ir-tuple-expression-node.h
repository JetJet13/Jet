//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_TUPLE_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include "../ir-node.h"
#include "../ir-instruction-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "../../ir-type/ir-struct-type.h"
#include "ir-expression-node.h"

class IRTupleExpressionNode : public IRExpressionNode {
private:
    ASTTupleExpressionNode* _node;
    IRInstructionNode* _irValue;
    std::vector<IRExpressionNode*> _irValues;
    IRType* _type;
public:
    IRTupleExpressionNode(ASTTupleExpressionNode* node, IRInstructionNode* irValue, IRType* type, std::vector<IRExpressionNode*> irValues);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* getValue() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    IRType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_EXPRESSION_NODE_H
