//
// Created by Johny Georges on 2025-04-12.
//

#ifndef JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H
#define JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-type/ir-ref-type.h"
#include "../../../ir-type/ir-new-class-instance-type.h"
#include "../../../ir-type/ir-captured-variable-type.h"
#include "../../../ir-type/ir-function-parameter-type.h"
#include "../../../ir-type/ir-lambda-type.h"
#include "../../../ir-type/ir-class-instance-type.h"

class TypeValueIRInjectorStrategy {
private:
    llvm::Value* inject(IRArrayPointerType* irArrayPointerType, IRBlockNode* irBlock);
    llvm::Value* inject(IRStructType* irStructType, IRBlockNode* irBlock);
    llvm::Value* inject(IRPointerType* irPointerType, IRBlockNode* irBlock);
    llvm::Value* inject(IRRefType* irRefType, IRBlockNode* irBlock);
    llvm::Value* inject(IRCapturedVariableType* irCapturedVariableType, IRBlockNode* irBlock);
    llvm::Value* inject(IRStructRefType* irStructRefType, IRBlockNode* irBlock);
    llvm::Value* inject(IRFunctionParameterType* irFunctionParameterType, IRBlockNode* irBlock);
    llvm::Value* inject(IRLambdaType* irLambdaType, IRBlockNode* irBlock);
    llvm::Value* inject(IRClassInstanceType* irClassInstanceType, IRBlockNode* irBlock);
    llvm::Value* inject(IRNewClassInstanceType* irNewClassInstanceType, IRBlockNode* irBlock);
public:
    llvm::Value* inject(IRType* irType, IRBlockNode* irBlock);
};

#endif //JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H
