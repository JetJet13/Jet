//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_ARRAY_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../ir-instruction-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-array-pointer-type.h"


class IRArrayExpressionNode : public IRExpressionNode {
private:
    ASTArrayExpressionNode* _node;
    IRInstructionNode* _irValue;
    IRInstructionNode* _arrayPointerSourceAllocation;
    std::vector<IRExpressionNode*> _irValues;
    IRArrayPointerType* _type;
public:
    IRArrayExpressionNode(ASTArrayExpressionNode* node, IRInstructionNode* irValue, IRInstructionNode* arrayPointerSourceAllocation, std::vector<IRExpressionNode*> irValues, IRArrayPointerType* type);
    llvm::Value* getValue() override;
    std::vector<IRExpressionNode*>* getValues();
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    IRInstructionNode* getSourceArrayAllocation();
    IRInstructionNode* getArrayPointerAllocation();
    IRArrayPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    unsigned long size();
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_ARRAY_EXPRESSION_NODE_H
