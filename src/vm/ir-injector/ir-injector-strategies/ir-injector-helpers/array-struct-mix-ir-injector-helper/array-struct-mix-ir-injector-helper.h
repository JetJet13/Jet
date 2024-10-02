//
// Created by Johny Georges on 2024-10-01.
//

#ifndef JETLANG_ARRAY_STRUCT_MIX_IR_INJECTOR_HELPER_H
#define JETLANG_ARRAY_STRUCT_MIX_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"
#include "../../../ir-injector-map.h"
#include "../../../../ir-nodes/ir-module-node.h"

class ArrayStructMixIRInjectorHelper {
public:
    static llvm::Value* extractAllocation(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule);
    static llvm::Value* extractAllocation(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule);
};

#endif //JETLANG_ARRAY_STRUCT_MIX_IR_INJECTOR_HELPER_H
