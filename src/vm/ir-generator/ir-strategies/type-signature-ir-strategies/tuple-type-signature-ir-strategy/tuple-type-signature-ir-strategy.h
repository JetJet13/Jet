//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_TUPLE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_TUPLE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/tuple-type-signature/tuple-type-signature.h"

class TupleTypeSignatureIRStrategy {
public:
    IRStructType* generate(TupleTypeSignature* tupleTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_TUPLE_TYPE_SIGNATURE_IR_STRATEGY_H
