//
// Created by Johny Georges on 2025-03-24.
//

#include "pointer-ir-injector-helper.h"
#include "../array-ir-injector-helper/array-ir-injector-helper.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRInjectorHelper::injectPointerCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, std::shared_ptr<IRInstructionNode> sourceValueAllocation, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector) {
    auto loadedValue = InstructionIRInjectorHelper::injectLoad(sourceValueAllocation, irBlock);
    auto newValueAllocation = PointerIRInjectorHelper::injectPointerSourceAllocation(irBlock, irPointerType, loadedValue, irModule);
    auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getType());
    if (irPointerType->getUnderlyingType()->isArrayPointerType()) {
        auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayPointer(irBlock, sourceValueAllocation, irModule, irInjector);
        InstructionIRInjectorHelper::injectStore(loadedArrayPointer->getValue(), newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
    } else if (irPointerType->getUnderlyingType()->isStructType()) {
        auto loadedNestedStruct = StructIRInjectorHelper::injectStructRef(irBlock, sourceValueAllocation, irModule,
                                                                          irInjector);
        InstructionIRInjectorHelper::injectStore(loadedNestedStruct, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
    } else {
        InstructionIRInjectorHelper::injectStore(loadedValue, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
    }
    InstructionIRInjectorHelper::injectStore(newValueAllocation->getValue(), newPointer, irBlock, newValueAllocation->getIRType()->getUnderlyingType());
    return newPointer;
}

llvm::Value* PointerIRInjectorHelper::injectPointerCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourcePointer, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector) {
    auto loadedValue = InstructionIRInjectorHelper::injectLoad(irPointerType, sourcePointer, irBlock);
    auto newValueAllocation = PointerIRInjectorHelper::injectPointerSourceAllocation(irBlock, irPointerType, loadedValue, irModule);
    auto newPointer = irBlock->getBuilder()->get()->CreateAlloca(irPointerType->getType());
    if (irPointerType->getUnderlyingType()->isArrayPointerType()) {
        auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irPointerType->getUnderlyingType());
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType));
        auto loadedArrayPointer = ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule,  loadedValue, arrayPointerAllocation, irInjector);
        InstructionIRInjectorHelper::injectStore(loadedArrayPointer->getValue(), newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getSourceType());
    } else if (irPointerType->getUnderlyingType()->isStructRefType()) {
        auto structRefType = std::dynamic_pointer_cast<IRStructRefType>(irPointerType->getSourceType());
        auto loadedNestedStruct = StructIRInjectorHelper::injectStructRefCopy(irBlock, structRefType, loadedValue,
                                                                              irModule, irInjector);
        InstructionIRInjectorHelper::injectStore(loadedNestedStruct, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
    } else {
        InstructionIRInjectorHelper::injectStore(loadedValue, newValueAllocation->getValue(), irBlock, newValueAllocation->getIRType()->getUnderlyingType());
    }
    InstructionIRInjectorHelper::injectStore(newValueAllocation->getValue(), newPointer, irBlock, newValueAllocation->getIRType()->getUnderlyingType());
    return newPointer;
}

std::shared_ptr<IRInstructionNode> PointerIRInjectorHelper::injectPointerSourceAllocation(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourceValue, std::shared_ptr<IRModuleNode> irModule) {

    if (irPointerType->getSourceType()->isArrayPointerType()) {
        auto irArrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irPointerType->getSourceType());
        auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
        auto numElementsIndex = irBlock->getBuilder()->get()->getInt64(irArrayPointerType->getNumElementsIndex());
        auto pointerToNumElements = irBlock->getBuilder()->get()->CreateInBoundsGEP(irArrayPointerType->getType(), sourceValue, { zeroIndex, numElementsIndex });
        auto numElements = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getNumElementsType(), pointerToNumElements);
        return ArrayIRInjectorHelper::injectArrayAllocation(irBlock, irArrayPointerType, numElements, irModule);
    }

    auto allocation = IRInstructionNodeFactory::create(irPointerType->getSourceType());
    irBlock->getBuilder()->get()->Insert(allocation->getValue());
    return allocation;
}