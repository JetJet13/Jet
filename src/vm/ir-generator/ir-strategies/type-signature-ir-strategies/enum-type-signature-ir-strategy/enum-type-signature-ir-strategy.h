//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../ir-type/ir-enum-type.h"

class EnumTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRType> generate(std::shared_ptr<EnumTypeSignature> enumTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IREnumType> generate(std::shared_ptr<EnumTypeSignature> enumTypeSignature, std::vector<llvm::Constant*> enumValues, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H
