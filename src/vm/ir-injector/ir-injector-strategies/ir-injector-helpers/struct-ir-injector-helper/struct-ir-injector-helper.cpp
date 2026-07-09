//
// Created by Johny Georges on 2024-09-14.
//

#include "struct-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../pointer-ir-injector-helper/pointer-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"

llvm::Value* StructIRInjectorHelper::injectStructRef(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> structRefAllocation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector) {
    auto irStructRefType = std::dynamic_pointer_cast<IRStructRefType>(structRefAllocation->getIRType()->getUnderlyingType());
    auto irStructType = irStructRefType->getStructIRType();
    auto destinationStructRefAllocation = IRInstructionNodeFactory::create(structRefAllocation);
    InstructionIRInjectorHelper::inject(destinationStructRefAllocation, irBlock);
    auto destinationStructMalloc = irBlock->getBuilder()->get()->CreateCall(irModule->getMallocFunction(), {
        irBlock->getBuilder()->get()->getInt64(1),
        irBlock->getBuilder()->get()->getInt64(irStructType->getSizeInBytes())
    });
    auto destinationCounterAllocation = irBlock->getBuilder()->get()->CreateCall(irModule->getMallocFunction(), {
            irBlock->getBuilder()->get()->getInt64(1),
            irBlock->getBuilder()->get()->getInt64(irStructRefType->getCounterIRType()->getSizeInBytes())
    });
    auto sourceStructAllocation = structRefAllocation->getParentAllocation().value();
    for (unsigned long i = 0; i < irStructType->size(); ++i) {
        auto irTypeAtIndex = irStructType->getIRTypeByIndex(i);
        auto destinationPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructType->getType(), destinationStructMalloc, i);
        if (irTypeAtIndex->isArrayPointerType()) {
            auto arrayPointerAllocation = structRefAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto typeValue = irInjector->inject(irBlock, irTypeAtIndex, irModule);
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getValue()->getAllocatedType(), typeValue, irBlock, irTypeAtIndex);
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getCopyArrayFunction(),
                    {
                        destinationPointer,
                        arrayPointerAllocation->getValue(),
                        loadedTypeValue
                    }
            );
        } else if (irTypeAtIndex->isStructRefType()) {
            auto nestedStructAllocation = sourceStructAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructRef(irBlock, nestedStructAllocation, irModule,
                                                                              irInjector);
            InstructionIRInjectorHelper::injectStore(loadedNestedStruct, destinationPointer, irBlock, irTypeAtIndex);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerAllocation = sourceStructAllocation->getChildAllocationForKey(irStructType->getKeyForIndex(i));
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, std::dynamic_pointer_cast<IRPointerType>(irTypeAtIndex), pointerAllocation, irModule, irInjector);
            InstructionIRInjectorHelper::injectStore(loadedPointer, destinationPointer, irBlock);
        } else {
            auto elementPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructType->getType(), sourceStructAllocation->getValue(), i);
            auto loadedValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getType(), elementPointer, irBlock, irTypeAtIndex);
            InstructionIRInjectorHelper::injectStore(loadedValue, destinationPointer, irBlock);
        }
    }
    auto pointerToStructPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), destinationStructRefAllocation->getValue(), irStructRefType->getStructIndex());
    InstructionIRInjectorHelper::injectStore(destinationStructMalloc, pointerToStructPointer, irBlock);
    auto pointerToCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), destinationStructRefAllocation->getValue(), irStructRefType->getCounterIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(1), destinationCounterAllocation, irBlock);
    InstructionIRInjectorHelper::injectStore(destinationCounterAllocation, pointerToCounterPointer, irBlock);
    return InstructionIRInjectorHelper::injectLoad(destinationStructRefAllocation->getAllocatedType(), destinationStructRefAllocation->getValue(), irBlock);
}

llvm::Value* StructIRInjectorHelper::injectStructRefCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRStructRefType> irStructRefType, llvm::Value* structRefSource, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector) {
    auto destinationStructRefAllocation = irBlock->getBuilder()->get()->CreateAlloca(irStructRefType->getType());
    StructIRInjectorHelper::injectStructRefCopy(irBlock, irStructRefType, structRefSource, destinationStructRefAllocation, irModule, irInjector);
    return InstructionIRInjectorHelper::injectLoad(destinationStructRefAllocation->getAllocatedType(), destinationStructRefAllocation, irBlock, irStructRefType);
}

llvm::Value* StructIRInjectorHelper::injectStructRefCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRStructRefType> irStructRefType, llvm::Value* structRefSource, llvm::Value* structRefDestination, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector) {
    auto destinationStructAllocation = irBlock->getBuilder()->get()->CreateCall(irModule->getMallocFunction(), {
            irBlock->getBuilder()->get()->getInt64(1),
            irBlock->getBuilder()->get()->getInt64(irStructRefType->getStructIRType()->getSizeInBytes()),
    });
    auto destinationCounterAllocation = irBlock->getBuilder()->get()->CreateCall(irModule->getMallocFunction(), {
            irBlock->getBuilder()->get()->getInt64(1),
            irBlock->getBuilder()->get()->getInt64(irStructRefType->getCounterIRType()->getSizeInBytes())
    });
    auto loadedStructRef = InstructionIRInjectorHelper::injectLoad(irStructRefType->getType(), structRefSource, irBlock, irStructRefType);
    auto structSource = irBlock->getBuilder()->get()->CreateExtractValue(loadedStructRef, irStructRefType->getStructIndex());
    for (unsigned long i = 0; i < irStructRefType->getStructIRType()->size(); ++i) {
        auto irTypeAtIndex = irStructRefType->getStructIRType()->getIRTypeByIndex(i);
        auto destinationPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), destinationStructAllocation, i);
        auto pointerToStructValue = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getStructIRType()->getType(), structSource, i);
        if (irTypeAtIndex->isArrayPointerType()) {
            auto typeValue = irInjector->inject(irBlock, irTypeAtIndex, irModule);
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getValue()->getAllocatedType(), typeValue, irBlock, irTypeAtIndex);
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getCopyArrayFunction(),
                    {
                            destinationPointer,
                            pointerToStructValue,
                            loadedTypeValue
                    }
            );
        } else if (irTypeAtIndex->isStructRefType()) {
            auto structRefType = std::dynamic_pointer_cast<IRStructRefType>(irTypeAtIndex);
            auto loadedNestedStruct = StructIRInjectorHelper::injectStructRefCopy(irBlock, structRefType,
                                                                                  pointerToStructValue, irModule,
                                                                                  irInjector);
            InstructionIRInjectorHelper::injectStore(loadedNestedStruct, destinationPointer, irBlock, irTypeAtIndex);
        } else if (irTypeAtIndex->isPointerType()) {
            auto pointerType = std::dynamic_pointer_cast<IRPointerType>(irTypeAtIndex);
            auto loadedPointer = PointerIRInjectorHelper::injectPointerCopy(irBlock, pointerType, pointerToStructValue, irModule, irInjector);
            InstructionIRInjectorHelper::injectStore(loadedPointer, destinationPointer, irBlock, irTypeAtIndex);
        } else {
            auto loadedValue = InstructionIRInjectorHelper::injectLoad(irTypeAtIndex->getType(), pointerToStructValue, irBlock, irTypeAtIndex);
            InstructionIRInjectorHelper::injectStore(loadedValue, destinationPointer, irBlock, irTypeAtIndex);
        }
    }
    auto pointerToStructPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), structRefDestination, irStructRefType->getStructIndex());
    InstructionIRInjectorHelper::injectStore(destinationStructAllocation, pointerToStructPointer, irBlock);
    auto pointerToCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irStructRefType->getType(), structRefDestination, irStructRefType->getCounterIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(1), destinationCounterAllocation, irBlock);
    InstructionIRInjectorHelper::injectStore(destinationCounterAllocation, pointerToCounterPointer, irBlock);
    return structRefDestination;
}