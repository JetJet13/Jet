//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_STRING_IR_INJECTOR_H
#define JETLANG_STRING_IR_INJECTOR_H

#include "../ir-injector.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-nodes/ir-instruction-node.h"

class IRStringLiteralExpressionNode;

class StringIRInjector : public IRInjector {
private:
    llvm::LoadInst* injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRInstructionNode* arrayPointerAllocation);
    llvm::LoadInst* injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRInstructionNode* arrayAllocation, llvm::AllocaInst* arrayPointerAllocation);
public:
    llvm::Value* inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* inject(IRStringLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_STRING_IR_INJECTOR_H
