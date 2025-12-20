//
// Created by Johny Georges on 2024-12-31.
//

#include "class-instance-type-signature-ir-strategy.h"

IRClassInstanceType* ClassInstanceTypeSignatureIRStrategy::generate(ClassInstanceTypeSignature* classInstanceTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : classInstanceTypeSignature->getClassTypeSignature()->getProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
            std::pair(keyValue.first, classInstanceTypeSignature->getClassTypeSignature()->getProperties()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));

    }
    auto classInstanceProperties = new IRStructType(llvm::StructType::get(**irContext->getContext(), classPropertyTypes), keyIndexMap, keyTypeMap);
    classInstanceProperties->setAlignmentAndSizeForIRTypes();
    classInstanceProperties->setKeyId(classInstanceTypeSignature->getKeyId());
    classInstanceProperties->setId(classInstanceTypeSignature->getClassTypeSignature()->getId());
    classInstanceProperties->setValue(irGenerator->generateIRTypeValueFor(classInstanceProperties, irContext));
    auto classInstancePropertiesPointerType = irGenerator->generateIRStructRefType(classInstanceProperties);
    classInstancePropertiesPointerType->setKeyId(classInstanceTypeSignature->getKeyId());
    classInstancePropertiesPointerType->setId(classInstanceTypeSignature->getClassTypeSignature()->getId());
    classInstancePropertiesPointerType->setValue(irGenerator->generateIRTypeValueFor(classInstancePropertiesPointerType, irContext));

    auto irClassType = (IRClassType*)scope->findType(classInstanceTypeSignature->getClassTypeSignature()->getId()).value();
    auto irType = new IRClassInstanceType(
        irClassType,
        irClassType->getIRTypeForConstructor(classInstanceTypeSignature->getConstructorId()).value(),
        classInstancePropertiesPointerType
    );
    irType->setId(classInstanceTypeSignature->getClassTypeSignature()->getId());
    irType->setKeyId(classInstanceTypeSignature->getKeyId());
    return irType;
}