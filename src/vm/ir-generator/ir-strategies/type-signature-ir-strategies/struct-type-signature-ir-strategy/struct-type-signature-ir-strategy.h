//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_STRUCT_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_STRUCT_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/struct-type-signature/struct-type-signature.h"
#include "../../../../ir-type/ir-struct-ref-type.h"

class StructTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRStructRefType> generate(std::shared_ptr<StructTypeSignature> structTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRStructType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRStructRefType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_STRUCT_TYPE_SIGNATURE_IR_STRATEGY_H
