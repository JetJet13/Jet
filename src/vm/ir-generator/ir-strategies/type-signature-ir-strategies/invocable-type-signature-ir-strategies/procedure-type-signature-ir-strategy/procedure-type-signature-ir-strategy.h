//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_PROCEDURE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_PROCEDURE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-generator.h"
#include "../../../../../../core/type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../../../ir-type/ir-function-type.h"

class ProcedureTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRFunctionType> generate(std::shared_ptr<ProcedureTypeSignature> procedureTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_PROCEDURE_TYPE_SIGNATURE_IR_STRATEGY_H
