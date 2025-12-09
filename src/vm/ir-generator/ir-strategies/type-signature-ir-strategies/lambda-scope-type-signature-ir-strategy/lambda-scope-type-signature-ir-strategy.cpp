//
// Created by Johny Georges on 2025-11-21.
//

#include "lambda-scope-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"

IRStructType* LambdaScopeTypeSignatureIRStrategy::generate(LambdaScopeTypeSignature* lambdaScopeTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto structPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    auto capturedVariableIds = lambdaScopeTypeSignature->getCapturedVariableIds();
    int i = 0;
    for (auto capturedVariableId : *capturedVariableIds) {
        auto irVariableType = scope->find(capturedVariableId).value()->getIRType()->getSourceType();
        // todo - with the introduction of lambda cleanup functions, we need to inject the same
        //  type value in multiple function blocks which is problematic because the type-value
        // allocations can only be injected in one block only. To get around this, one approach
        // we can take is to add clone logic for type-values.
        // TODO - implement ir-type 'clone' method override for aggregate ir-types.
        auto irCapturedVariableType = irGenerator->generateIRCapturedVariableType(irVariableType->clone());
        irCapturedVariableType->setValue(this->generateTypeValue(irCapturedVariableType, irGenerator, irContext));
        structPropertyTypes.push_back(irCapturedVariableType->getType());
        keyIndexMap.insert(
                std::pair(capturedVariableId, i)
        );
        keyTypeMap.insert(std::pair(capturedVariableId, irCapturedVariableType));
        i++;
    }
    auto structType = new IRStructType(llvm::StructType::get(**irContext->getContext(), structPropertyTypes), keyIndexMap, keyTypeMap);
    structType->setValue(irGenerator->generateIRTypeValueFor(structType, irContext));
    return structType;
}

IRTypeValueInstructionNode* LambdaScopeTypeSignatureIRStrategy::generateTypeValue(IRCapturedVariableType* irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto allocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.CAPTURED_VARIABLE),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, allocation, irTypeValueType);
    return new IRTypeValueInstructionNode(
            allocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}