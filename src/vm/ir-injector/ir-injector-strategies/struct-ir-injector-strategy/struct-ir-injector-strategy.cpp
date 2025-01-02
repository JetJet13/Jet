//
// Created by Johny Georges on 2024-08-14.
//

#include "struct-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* StructIRInjectorStrategy::inject(IRExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_STRUCT_EXPRESSION_NODE)) {
        return this->inject((IRStructExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRGlobalIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRTupleAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionInvocationExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionParameterInvocationExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRClassPropertyAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    }
    throw std::logic_error("StructIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StructIRInjectorStrategy::inject(IRStructExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto structExpressionAllocation = builder->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getIRType()->getType(), structExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjectorMap->getInjector(irExpressionAtIndex->getTypeSignature())
                ->inject(irExpressionAtIndex, builder, irInjectorMap, irOperationType, irModule, scope);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return builder->get()->CreateLoad(irExpression->getIRType()->getType(), structExpressionAllocation);
}

llvm::Value* StructIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_OPERAND_OP) {
        return irExpression->getValue();
    }
    return StructIRInjectorHelper::injectStructCopy(
            builder,
            (IRStructType*)irExpression->getIRType()->getSourceType(),
            irExpression->getValue(),
            irModule
    );
}

llvm::Value* StructIRInjectorStrategy::inject(IRGlobalIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedStruct = builder->get()->CreateLoad(irExpression->getValue()->getValueType(), irExpression->getValue());
    if (irOperationType == IR_OPERAND_OP) {
        return loadedStruct;
    }

    return StructIRInjectorHelper::injectStructCopy(
            builder,
            (IRStructType*)irExpression->getSourceAllocation().value()->getIRType()->getSourceType(),
            loadedStruct,
            irModule
    );
}

llvm::Value* StructIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedSourceAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    if (irOperationType == IR_OPERAND_OP) {
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(loadedSourceAllocation->getType(), loadedSourceAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        builder->get()->Insert(pointer);
        return builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    }
    return StructIRInjectorHelper::injectStructCopy(
            builder,
            (IRStructType*)irExpression->getSource()->getIRType(),
            loadedSourceAllocation,
            irModule
    );
}

llvm::Value* StructIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_OPERAND_OP) {
        auto loadedPointerToIndexedElement = irInjectorMap->getInjector(irExpression->getSourceExpression()->getTypeSignature())->inject(irExpression->getSourceExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
        auto indexValue = irInjectorMap->getInjector(irExpression->getIndexExpression()->getTypeSignature())->inject(irExpression->getIndexExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
        auto pointerToIndexedElement = builder->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), loadedPointerToIndexedElement, { indexValue });
        return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
    }
    throw std::logic_error("StructIRInjectorStrategy not implemented for IRArrayAccessExpressionNode + irOperationType");
}

llvm::Value* StructIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedSourceAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    if (irOperationType == IR_OPERAND_OP) {
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(loadedSourceAllocation->getType(), loadedSourceAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        builder->get()->Insert(pointer);
        return builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    }
    return StructIRInjectorHelper::injectStructCopy(
            builder,
            (IRStructType*)irExpression->getSource()->getIRType(),
            loadedSourceAllocation,
            irModule
    );
}

llvm::Value* StructIRInjectorStrategy::inject(IRFunctionInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, builder, irInjectorMap, irModule, scope);
}

llvm::Value* StructIRInjectorStrategy::inject(IRFunctionParameterInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, builder, irInjectorMap, irModule, scope);
}

llvm::Value* StructIRInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto allocation = builder->get()->CreateAlloca(irExpression->getTargetIRType()->getType());
    auto loadedStruct = ClassPropertyAccessIRInjectorHelper::inject(irExpression, builder, irInjectorMap, irModule, scope);
    builder->get()->CreateStore(loadedStruct, allocation);
    return allocation;
}