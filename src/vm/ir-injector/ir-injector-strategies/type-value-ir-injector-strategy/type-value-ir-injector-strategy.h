//
// Created by Johny Georges on 2025-04-12.
//

#ifndef JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H
#define JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../../../ir-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-type/ir-array-pointer-type.h"

class TypeValueIRInjectorStrategy {
private:
    llvm::Value* inject(IRArrayPointerType* irArrayPointerType, IRBlockNode* irBlock);
    llvm::Value* inject(IRStructType* irStructType, IRBlockNode* irBlock);
    llvm::Value* inject(IRPointerType* irArrayPointerType, IRBlockNode* irBlock);
public:
    llvm::Value* inject(IRType* irType, IRBlockNode* irBlock);
};

#endif //JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H
