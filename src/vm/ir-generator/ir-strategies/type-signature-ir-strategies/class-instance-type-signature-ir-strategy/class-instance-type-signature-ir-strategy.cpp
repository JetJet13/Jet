//
// Created by Johny Georges on 2024-12-31.
//

#include "class-instance-type-signature-ir-strategy.h"

IRClassInstanceType* ClassInstanceTypeSignatureIRStrategy::generate(ClassInstanceTypeSignature* classInstanceTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto irClassType = (IRClassType*)scope->findType(classInstanceTypeSignature->getClassTypeSignature()->getId()).value();
    return new IRClassInstanceType(
        irClassType,
        irClassType->getIRTypeForConstructor(classInstanceTypeSignature->getConstructorId()).value()
    );
}