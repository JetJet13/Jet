//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_PARAMETER_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_PARAMETER_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-type/ir-parameter-type.h"

class ParameterTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRParameterType> generate(std::shared_ptr<ParameterListItemTypeSignature> parameterListItemTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_PARAMETER_TYPE_SIGNATURE_IR_STRATEGY_H
