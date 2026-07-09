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
    std::shared_ptr<IRStructRefType> generate(std::shared_ptr<TupleTypeSignature> tupleTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_TUPLE_TYPE_SIGNATURE_IR_STRATEGY_H
