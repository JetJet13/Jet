//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/class-type-signature/class-type-signature.h"
#include "../../../../ir-type/ir-class-type.h"

class ClassTypeSignatureIRStrategy {
public:
    IRClassType* generate(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRClassType* generateInitial(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRClassType* generatePostInitial(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H
