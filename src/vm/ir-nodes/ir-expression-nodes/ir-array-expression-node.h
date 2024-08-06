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
#include "../ir-array-node.h"


class IRArrayExpressionNode : public IRExpressionNode {
private:
    ASTArrayExpressionNode* _node;
    IRInstructionNode* _irValue;
    std::vector<IRExpressionNode*> _irValues;
    IRArrayNode* _array;
    IRPointerType* _type;
public:
    IRArrayExpressionNode(ASTArrayExpressionNode* node, IRInstructionNode* irValue, std::vector<IRExpressionNode*> irValues, IRArrayNode* array, IRPointerType* type);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* getValue() override;
    IRInstructionNode* getSourceAllocation() override;
    IRPointerType* getIRType() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_ARRAY_EXPRESSION_NODE_H
