//
// Created by Johny Georges on 2024-07-10.
//

#include "literal-type-signature-ir-strategy.h"

IRType* LiteralTypeSignatureIRStrategy::generate(LiteralTypeSignature* literalTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    if (literalTypeSignature->typeSourceIs(INT_LITERAL_TYPE_SOURCE)) {
        return new IRType(llvm::IntegerType::get(**irContext->getContext(), 32));
    } else if (literalTypeSignature->typeSourceIs(FLOAT_LITERAL_TYPE_SOURCE)) {
        return new IRType(llvm::ConstantFP::get(**irContext->getContext(), llvm::APFloat(0.0))->getType());
    } else if (literalTypeSignature->typeSourceIs(CHAR_LITERAL_TYPE_SOURCE)) {
        return new IRType(llvm::IntegerType::get(**irContext->getContext(), 8));
    } else if (literalTypeSignature->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto charType = llvm::IntegerType::get(**irContext->getContext(), 8);
        return irGenerator->generateIrArrayPointerType(new IRType(charType));
    } else {
        return new IRType(llvm::IntegerType::get(**irContext->getContext(), 1));
    }
}