//
// Created by Johny Georges on 2024-12-31.
//

#include "class-instance-type-signature-ir-strategy.h"

IRClassInstanceType* ClassInstanceTypeSignatureIRStrategy::generate(ClassInstanceTypeSignature* classInstanceTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    return new IRClassInstanceType(
        irGenerator->generateTypeFor(classInstanceTypeSignature->getClassTypeSignature()),
        (IRFunctionType*)irGenerator->generateTypeFor(classInstanceTypeSignature->getConstructorTypeSignature())
    );
}