//
// Created by Johny Georges on 2026-01-10.
//

#include "jet-debug-type-signature-map.h"
#include "../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../type-signature/struct-type-signature/struct-type-signature.h"
#include "../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"

std::string JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignatureKey() {
    return "assertDebugRefCount";
}

std::string JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignatureKey() {
    return "assertDebugStructRefCount";
}

std::string JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignatureKey() {
    return "assertDebugLambdaRefCount";
}

FunctionTypeSignature* JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignature() {
    auto assertDebugRefCountTypeSignature = new FunctionTypeSignature(
        new ParameterListTypeSignature({
            new ParameterListItemTypeSignature("refValue", (new RefTypeSignature(new VoidTypeSignature()))->markAsGeneric()),
            new ParameterListItemTypeSignature("expectedRefCount", new IntLiteralTypeSignature()),
        }),
        new VoidTypeSignature()
    );
    assertDebugRefCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugRefCountTypeSignature;
}

FunctionTypeSignature* JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignature() {
    auto assertDebugStructRefCountTypeSignature = new FunctionTypeSignature(
        new ParameterListTypeSignature({
            new ParameterListItemTypeSignature("structValue", (new StructTypeSignature())->markAsGeneric()),
            new ParameterListItemTypeSignature("expectedRefCount", new IntLiteralTypeSignature()),
        }),
        new VoidTypeSignature()
    );
    assertDebugStructRefCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_STRUCT_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugStructRefCountTypeSignature;
}

FunctionTypeSignature* JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignature() {
    auto assertDebugStructRefCountTypeSignature = new FunctionTypeSignature(
        new ParameterListTypeSignature({
            new ParameterListItemTypeSignature("lambdaValue", (new LambdaTypeSignature())->markAsGeneric()),
            new ParameterListItemTypeSignature("expectedRefCount", new IntLiteralTypeSignature()),
        }),
        new VoidTypeSignature()
    );
    assertDebugStructRefCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_LAMBDA_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugStructRefCountTypeSignature;
}