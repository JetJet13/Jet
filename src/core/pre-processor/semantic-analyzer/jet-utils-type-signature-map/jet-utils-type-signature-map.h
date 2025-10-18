//
// Created by Johny Georges on 2025-07-25.
//

#ifndef JETLANG_JET_UTILS_TYPE_SIGNATURE_MAP_H
#define JETLANG_JET_UTILS_TYPE_SIGNATURE_MAP_H

#include <optional>
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../../../type-signature/types/function-vararg-type-signature-map/function-vararg-type-signature-map.h"

class JetUtilsTypeSignatureMap {
public:
    static FunctionVarArgTypeSignatureMap* getPrintTypeSignatureMap();
    static std::string getPrintTypeSignatureKey();
    static std::string getRangeTypeSignatureKey();
    static std::string getRange2pTypeSignatureKey();
    static std::string getRange3pTypeSignatureKey();
    static std::string getAssertTypeSignatureKey();
    static std::string getAssertWithMessageTypeSignatureKey();
    static bool doesIdConflict(std::string id);
    static ProcedureTypeSignature* getPrintTypeSignature();
    static FunctionTypeSignature* getRangeTypeSignature();
    static FunctionTypeSignature* getRange2pTypeSignature();
    static FunctionTypeSignature* getRange3pTypeSignature();
    static FunctionTypeSignature* getAssertTypeSignature();
    static FunctionTypeSignature* getAssertWithMessageTypeSignature();
};

#endif //JETLANG_JET_UTILS_TYPE_SIGNATURE_MAP_H
