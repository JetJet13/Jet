//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_MODULE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_MODULE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../ir-type/ir-enum-type.h"
#include "../../../../../core/type-signature/module-type-signature/module-type-signature.h"
#include "../../../../ir-type/ir-module-type.h"

class ModuleTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRModuleType> generate(std::shared_ptr<ModuleTypeSignature> moduleTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_MODULE_TYPE_SIGNATURE_IR_STRATEGY_H
