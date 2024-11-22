//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-type/ir-parameter-list-type.h"

class ParameterListTypeSignatureIRStrategy {
public:
    IRParameterListType* generate(ParameterListTypeSignature* parameterListTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, std::optional<ParameterListItemTypeSignature*> scopeParameter = {});
};

#endif //JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_IR_STRATEGY_H
