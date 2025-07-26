//
// Created by Johny Georges on 2025-07-25.
//

#include "jet-utils-type-signature-map.h"
#include "../../../type-signature/literal-type-signature/literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../type-signature/array-type-signature/array-type-signature.h"

std::string JetUtilsTypeSignatureMap::getPrintTypeSignatureKey() {
    return "print";
}

std::string JetUtilsTypeSignatureMap::getRangeTypeSignatureKey() {
    return "range";
}

bool JetUtilsTypeSignatureMap::doesIdConflict(std::string id) {
    return id == JetUtilsTypeSignatureMap::getRangeTypeSignatureKey()
        || id == JetUtilsTypeSignatureMap::getPrintTypeSignatureKey();

}

ProcedureTypeSignature* JetUtilsTypeSignatureMap::getPrintTypeSignature() {
    auto parameterList = new ParameterListTypeSignature({
        new ParameterListItemTypeSignature("value", new LiteralTypeSignature())
    });
    parameterList->markAsVariableLength(0);
    auto printTypeSignature = new ProcedureTypeSignature(parameterList);
    printTypeSignature->markAsBuiltIn()->setId("jet.utils.print");
    return printTypeSignature;
}

FunctionTypeSignature* JetUtilsTypeSignatureMap::getRangeTypeSignature() {
    auto rangeTypeSignature = new FunctionTypeSignature(
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("value", new IntLiteralTypeSignature())
            }),
            new ArrayTypeSignature(new IntLiteralTypeSignature())
    );
    rangeTypeSignature->markAsBuiltIn()->setId("jet.utils.range");
    return rangeTypeSignature;
}