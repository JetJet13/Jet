//
// Created by Johny Georges on 2024-09-04.
//

#ifndef JETLANG_IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-array-pointer-type.h"
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"


class IRAggregateIdentifierExpressionNode : public IRExpressionNode {
private:
    ASTIdentifierExpressionNode* _node;
    IRInstructionNode* _arrayAllocation;
    IRInstructionNode* _arrayPointerAllocation;
    llvm::GetElementPtrInst* _intPointer;
    llvm::LoadInst* _loadedNumElements;
    IRInstructionNode* _sourceAllocation;
    IRArrayPointerType* _type;
public:
    IRAggregateIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irAllocation, IRInstructionNode* arrayPointerSourceAllocation, IRInstructionNode* sourceAllocation, llvm::GetElementPtrInst* intPointer, llvm::LoadInst* loadedNumElements, IRArrayPointerType* type);
    llvm::GetElementPtrInst* getIntPointer();
    llvm::LoadInst* getLoadedNumElements();
    llvm::Value* getValue() override;
    std::optional<IRInstructionNode*> getSourceAllocation() override;
    IRInstructionNode* getAggregateSourceAllocation();
    IRInstructionNode* getAggregateAllocation();
    IRInstructionNode* getAggregatePointerAllocation();
    IRArrayPointerType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    llvm::Type* getTypeAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE_H
