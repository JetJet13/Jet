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
    static std::shared_ptr<FunctionVarArgTypeSignatureMap> getPrintTypeSignatureMap();
    static std::string getPrintTypeSignatureKey();
    static std::string getRangeTypeSignatureKey();
    static std::string getRange2pTypeSignatureKey();
    static std::string getRange3pTypeSignatureKey();
    static std::string getAssertTypeSignatureKey();
    static std::string getAssertWithMessageTypeSignatureKey();
    static bool doesIdConflict(std::string id);
    static std::shared_ptr<ProcedureTypeSignature> getPrintTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getRangeTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getRange2pTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getRange3pTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getAssertTypeSignature();
    static std::shared_ptr<FunctionTypeSignature> getAssertWithMessageTypeSignature();
};

#endif //JETLANG_JET_UTILS_TYPE_SIGNATURE_MAP_H
