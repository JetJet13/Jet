//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_TUPLE_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "ir-expression-node.h"

class IRTupleExpressionNode : public IRExpressionNode {
private:
    ASTTupleExpressionNode* _astNode;
    llvm::AllocaInst* _irAllocation;
    std::vector<IRExpressionNode*> _irValues;
    llvm::GetElementPtrInst* _irPointer;
    std::vector<llvm::Value*> _irStatements;
    void generateStatements();
public:
    IRTupleExpressionNode(ASTTupleExpressionNode* astNode, llvm::AllocaInst* irAllocation, std::vector<IRExpressionNode*> irValues, llvm::GetElementPtrInst* irPointer);
    llvm::AllocaInst* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_EXPRESSION_NODE_H
