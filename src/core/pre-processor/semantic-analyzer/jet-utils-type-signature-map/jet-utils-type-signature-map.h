//
// Created by Johny Georges on 2025-07-25.
//

#ifndef JETLANG_JET_UTILS_TYPE_SIGNATURE_MAP_H
#define JETLANG_JET_UTILS_TYPE_SIGNATURE_MAP_H

#include <optional>
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"

class JetUtilsTypeSignatureMap {
public:
    static std::string getPrintTypeSignatureKey();
    static std::string getRangeTypeSignatureKey();
    static bool doesIdConflict(std::string id);
    static ProcedureTypeSignature* getPrintTypeSignature();
    static FunctionTypeSignature* getRangeTypeSignature();
};

#endif //JETLANG_JET_UTILS_TYPE_SIGNATURE_MAP_H
