//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_ARRAY_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "ir-constant-expression-node.h"


class IRArrayExpressionNode : public IRConstantExpressionNode {
private:
    ASTArrayExpressionNode* _node;
    llvm::Constant* _irValue;
    std::vector<IRExpressionNode*> _irValues;
    IRType* _type;
public:
    IRArrayExpressionNode(ASTArrayExpressionNode* node, llvm::Constant* irValue, std::vector<IRExpressionNode*> irValues, IRType* type);
    llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Constant* getValue() override;
    IRType* getIRType() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_ARRAY_EXPRESSION_NODE_H
