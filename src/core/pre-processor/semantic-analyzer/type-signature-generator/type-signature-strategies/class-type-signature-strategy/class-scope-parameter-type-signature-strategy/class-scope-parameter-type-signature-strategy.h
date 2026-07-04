//
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_CLASS_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"

class ClassScopeParameterTypeSignatureStrategy {
public:
    std::shared_ptr<ParameterListItemTypeSignature> create(std::shared_ptr<ClassTypeSignature> classTypeSignature);
};

#endif //JETLANG_CLASS_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H
