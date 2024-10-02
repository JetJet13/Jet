//
// Created by Johny Georges on 2024-10-01.
//

#include "array-struct-mix-ir-injector-helper.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"

// todo implement logic to handle expressions like:
//  myStruct.array[0].foo
//  myArray[0][1].foo
//  combo[0].structure.foo.bar[0][1]

llvm::Value* ArrayStructMixIRInjectorHelper::extractAllocation(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule) {
    auto sourceExpression = irExpression->getSource();
    if (sourceExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return ArrayStructMixIRInjectorHelper::extractAllocation((IRObjectAccessExpressionNode*)sourceExpression, builder, irInjectorMap, irModule);
    } else if (sourceExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return ArrayStructMixIRInjectorHelper::extractAllocation((IRArrayAccessExpressionNode*)sourceExpression, builder, irInjectorMap, irModule);
    }
    return StructIRInjectorHelper::extractNestedStructAllocation(irExpression)
            ->getChildAllocationForKey(*irExpression->getTargetKey())->getValue();
}

llvm::Value* ArrayStructMixIRInjectorHelper::extractAllocation(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule) {
    auto sourceExpression = irExpression->getSourceExpression();
    if (sourceExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return ArrayStructMixIRInjectorHelper::extractAllocation((IRObjectAccessExpressionNode*)sourceExpression, builder, irInjectorMap, irModule);
    } else if (sourceExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return ArrayStructMixIRInjectorHelper::extractAllocation((IRArrayAccessExpressionNode*)sourceExpression, builder, irInjectorMap, irModule);
    }
    return ArrayIRInjectorHelper::extractNestedArrayAllocation(builder, irExpression, irInjectorMap, irModule);
}