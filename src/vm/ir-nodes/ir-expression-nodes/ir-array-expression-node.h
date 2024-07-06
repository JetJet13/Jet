//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_ARRAY_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "ir-expression-node.h"

class IRArrayExpressionNode : public IRExpressionNode {
private:
    ASTArrayExpressionNode* _astNode;
    llvm::Constant* _irValue;
public:
    IRArrayExpressionNode(ASTArrayExpressionNode* astNode, llvm::Constant* irValue);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) override;
    llvm::Constant* getConstantIRValue() override;
    llvm::Constant* getIRValue() override;
    llvm::Type* getIRTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_ARRAY_EXPRESSION_NODE_H
