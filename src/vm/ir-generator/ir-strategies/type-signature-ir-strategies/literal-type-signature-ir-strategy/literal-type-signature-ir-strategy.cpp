//
// Created by Johny Georges on 2024-07-10.
//

#include "literal-type-signature-ir-strategy.h"

IRPointerType* LiteralTypeSignatureIRStrategy::generate(LiteralTypeSignature* literalTypeSignature, std::unique_ptr<llvm::LLVMContext>* context) {
    auto pointer = llvm::PointerType::get(**context, 0);
    if (literalTypeSignature->typeSourceIs(INT_LITERAL_TYPE_SOURCE)) {
        return new IRPointerType(
            pointer,
            new IRType(llvm::IntegerType::get(**context, 32))
        );
    } else if (literalTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)) {
        return new IRPointerType(
            pointer,
            new IRType(llvm::ConstantFP::get(**context, llvm::APFloat(0.0))->getType())
        );
    } else if (literalTypeSignature->typeSourceIs(CHAR_LITERAL_TYPE_SOURCE)) {
        return new IRPointerType(
            pointer,
            new IRType(llvm::IntegerType::get(**context, 8))
        );
    } else if (literalTypeSignature->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        return new IRPointerType(
            pointer,
            new IRType(llvm::IntegerType::get(**context, 8))
        );
    } else {
        return new IRPointerType(
            pointer,
            new IRType(llvm::IntegerType::get(**context, 1))
        );
    }
}