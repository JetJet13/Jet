//
// Created by Johny Georges on 2024-07-10.
//

#include "literal-type-signature-ir-strategy.h"

IRType* LiteralTypeSignatureIRStrategy::generate(LiteralTypeSignature* literalTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    if (literalTypeSignature->typeSourceIs(INT_LITERAL_TYPE_SOURCE)) {
        return new IRType(llvm::IntegerType::get(**context, 32));
    } else if (literalTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)) {
        return new IRType(llvm::ConstantFP::get(**context, llvm::APFloat(0.0))->getType());
    } else if (literalTypeSignature->typeSourceIs(CHAR_LITERAL_TYPE_SOURCE)) {
        return new IRType(llvm::IntegerType::get(**context, 8));
    } else if (literalTypeSignature->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto charType = llvm::IntegerType::get(**context, 8);
        return irGenerator->generateArrayPointerType(
                irGenerator->generatePointerType(charType),
                new IRType(charType)
        );
    } else {
        return new IRType(llvm::IntegerType::get(**context, 1));
    }
}