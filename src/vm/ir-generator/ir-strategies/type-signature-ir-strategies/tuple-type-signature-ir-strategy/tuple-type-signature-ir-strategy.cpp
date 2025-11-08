//
// Created by Johny Georges on 2024-07-11.
//

#include "tuple-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/md5/md5.h"

IRStructType* TupleTypeSignatureIRStrategy::generate(TupleTypeSignature* tupleTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto tupleElementTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    std::string id;
    for (int i = 0; i < tupleTypeSignature->size(); ++i) {
        auto tupleElement = tupleTypeSignature->getTypeSignatureAtIndex(i);
        auto tupleElementIrType = irGenerator->generateTypeFor(tupleElement, scope, irContext);
        tupleElementTypes.push_back(tupleElementIrType->getType());
        auto key = std::to_string(i);
        keyIndexMap.insert(std::pair(key, i));
        keyTypeMap.insert(std::pair(key, tupleElementIrType));
        id += "_" + key + "$" + tupleElementIrType->getId();
    }

    auto structType = new IRStructType(llvm::StructType::create(**irContext->getContext(), tupleElementTypes), keyIndexMap, keyTypeMap);
    structType->setId("tuple." + MD5().operator()(id));
    structType->setAlignmentAndSizeForIRTypes();
    structType->setValue(this->generateTypeValue(structType, irGenerator, irContext));
    return structType;
}

IRInstructionNode* TupleTypeSignatureIRStrategy::generateTypeValue(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto keys = std::vector<llvm::Constant*>();
    auto keyTypes = std::vector<llvm::Type*>();
    for (int i = 0; i < irType->size(); ++i) {
        auto key = irType->getKeyForIndex(i);
        auto keyAsValue = irGenerator->generateRawString(key);
        keys.push_back(keyAsValue);
        keyTypes.push_back(keyAsValue->getType());
    }
    auto structKeysType = llvm::ConstantStruct::get(llvm::StructType::get(**irContext->getContext(), keyTypes), keys);
    auto structKeysVariable = irContext->getModule()->getOrInsertGlobal(
            irType->getId(),
            structKeysType->getType(),
            [irContext, structKeysType, irType]() -> llvm::GlobalVariable* {
                return new llvm::GlobalVariable(
                        *irContext->getModule(),
                        structKeysType->getType(),
                        true,
                        llvm::GlobalValue::InternalLinkage,
                        structKeysType,
                        irType->getId()
                );
            }
    );
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(irType->size()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            structKeysVariable
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, typeValueTypeAllocation, irTypeValueType);
    return new IRInstructionNode(
            typeValueTypeAllocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            {},
            { storeInstruction }
    );
}