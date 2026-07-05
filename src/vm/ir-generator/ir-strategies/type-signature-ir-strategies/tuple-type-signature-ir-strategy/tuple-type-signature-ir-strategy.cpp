//
// Created by Johny Georges on 2024-07-11.
//

#include "tuple-type-signature-ir-strategy.h"
#include "../../../../types/ir-type-id.h"
#include "../../../../../shared/utils/md5/md5.h"

std::shared_ptr<IRStructRefType> TupleTypeSignatureIRStrategy::generate(std::shared_ptr<TupleTypeSignature> tupleTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto tupleElementTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyIdMap = std::unordered_map<unsigned long, std::string>();
    auto keyTypeMap = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (unsigned long i = 0; i < tupleTypeSignature->size(); ++i) {
        auto tupleElement = tupleTypeSignature->getTypeSignatureAtIndex(i);
        auto tupleElementIrType = irGenerator->generateTypeFor(tupleElement, scope, irContext);
        tupleElementTypes.push_back(tupleElementIrType->getType());
        auto key = std::to_string(i);
        keyIndexMap.insert(std::pair(key, i));
        keyIdMap.insert(std::pair(i, key));
        keyTypeMap.insert(std::pair(key, tupleElementIrType));
    }

    auto structType = std::make_shared<IRStructType>(llvm::StructType::get(**irContext->getContext(), tupleElementTypes), keyIndexMap, keyIdMap, keyTypeMap);
    structType->setAlignmentAndSizeForIRTypes();
    structType->setValue(irGenerator->generateIRTypeValueFor(structType, irContext));
    auto structRefType = irGenerator->generateIRStructRefType(structType);
    structRefType->setValue(irGenerator->generateIRTypeValueFor(structRefType, irContext));
    return structRefType;
}