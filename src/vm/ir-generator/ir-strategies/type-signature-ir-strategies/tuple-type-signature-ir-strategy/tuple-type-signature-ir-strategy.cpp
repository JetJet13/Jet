//
// Created by Johny Georges on 2024-07-11.
//

#include "tuple-type-signature-ir-strategy.h"

IRType* TupleTypeSignatureIRStrategy::generate(TupleTypeSignature* tupleTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto tupleElementTypes = std::vector<llvm::Type*>();
    for (auto tupleElement : *tupleTypeSignature->getElementTypes()) {
        tupleElementTypes.push_back(irGenerator->generateTypeFor(tupleElement)->getType());
    }
    return new IRType(llvm::StructType::get(**context, tupleElementTypes));
}