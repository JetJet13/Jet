//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector-strategy.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* StringIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRStringLiteralExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRAggregateIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionParameterInvocationExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
    throw std::logic_error("StringIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StringIRInjectorStrategy::inject(IRStringLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arrayAllocation = irExpression->getSourceAggregateAllocation()->getValue();
    irBlock->getBuilder()->get()->Insert(arrayAllocation);
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, irExpression->getIRType(), irExpression->getValue()->getType()->getArrayNumElements(),
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRAggregateIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, irBlock, irModule)->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    if (irExpression->getSource()->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto arrayAllocation = irExpression->getSourceAllocation().value()->getParentAllocation().value();
        irBlock->getBuilder()->get()->Insert(arrayAllocation->getValue());
        auto type = irExpression->getSource()->getIRType()->getSourceType()->getType()->getStructElementType(irExpression->getTargetKeyIndex());
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                irExpression->getSource()->getType(),
                irExpression->getSource()->getValue(),
                { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() }
        );
        irBlock->getBuilder()->get()->Insert(pointer);
        auto loaded = irBlock->getBuilder()->get()->CreateLoad(type, pointer);
        irBlock->getBuilder()->get()->CreateStore(loaded, arrayAllocation->getValue());
        return ArrayIRInjectorHelper::injectArrayPointer(
                irBlock,
                irArrayPointerType,
                type->getArrayNumElements(),
                arrayAllocation,
                irExpression->getSourceAllocation().value())->getValue();
    }
    auto arrayAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    return ArrayIRInjectorHelper::injectArrayCopy(irBlock, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto elementIrType = ((IRArrayPointerType*)irExpression->getIRType()->getSourceType())->getElementIRType();
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_OP, irModule, scope);
    if (irOperationType == IR_ASSIGNMENT_OP) {
        auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_OP, irModule, scope);
        auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), loadedPointerToIndexedElement, { indexValue });
        return pointerToIndexedElement;
    }

    return ArrayIRInjectorHelper::injectArrayCopy(
            irBlock,
            arrayPointerType,
            elementIrType,
            irModule,
            loadedPointerToIndexedElement,
            irExpression->getSourceAllocation().value()
    )->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto arrayAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    return ArrayIRInjectorHelper::injectArrayCopy(irBlock, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(std::string rawString, IRArrayPointerType* stringPointerType, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto stringAllocation = irBlock->getBuilder()->get()->CreateAlloca(stringPointerType->getElementType(), rawString.size());
    auto sourceAllocation = IRInstructionNodeFactory::create(stringAllocation, IRPointerType::create(stringPointerType->getElementIRType()));
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(stringPointerType));
    arrayPointerAllocation->setParentAllocation(sourceAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, stringPointerType, rawString.size(), sourceAllocation, arrayPointerAllocation)->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
}

llvm::Value* StringIRInjectorStrategy::inject(IRFunctionParameterInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
}

llvm::Value* StringIRInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto loadedPointerToIndexedElement = ClassPropertyAccessIRInjectorHelper::inject(irExpression,
                                                                                     irBlock,
                                                                                     irInjector,
                                                                                     irModule, scope);
    return ArrayIRInjectorHelper::injectArrayCopy(irBlock, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
}