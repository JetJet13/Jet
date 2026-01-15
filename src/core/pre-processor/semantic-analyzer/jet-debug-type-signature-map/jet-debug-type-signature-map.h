//
// Created by Johny Georges on 2026-01-10.
//

#ifndef JETLANG_JET_DEBUG_TYPE_SIGNATURE_MAP_H
#define JETLANG_JET_DEBUG_TYPE_SIGNATURE_MAP_H

#include <optional>
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../../../type-signature/types/function-vararg-type-signature-map/function-vararg-type-signature-map.h"

class JetDebugTypeSignatureMap {
public:
    static std::string getAssertDebugRefCountTypeSignatureKey();
    static std::string getAssertDebugStructRefCountTypeSignatureKey();
    static std::string getAssertDebugLambdaRefCountTypeSignatureKey();
    static FunctionTypeSignature* getAssertDebugRefCountTypeSignature();
    static FunctionTypeSignature* getAssertDebugStructRefCountTypeSignature();
    static FunctionTypeSignature* getAssertDebugLambdaRefCountTypeSignature();
};

#endif //JETLANG_JET_DEBUG_TYPE_SIGNATURE_MAP_H
