//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_PROCEDURE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_PROCEDURE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-generator.h"
#include "../../../../../../core/type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"

class ProcedureTypeSignatureIRStrategy {
public:
    IRType* generate(ProcedureTypeSignature* procedureTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_PROCEDURE_TYPE_SIGNATURE_IR_STRATEGY_H
