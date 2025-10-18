//
// Created by Johny Georges on 2025-07-25.
//

#include "jet-utils-type-signature-map.h"
#include "../../../type-signature/literal-type-signature/literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../type-signature/array-type-signature/array-type-signature.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../type-signature/literal-type-signature/string-literal-type-signature.h"

FunctionVarArgTypeSignatureMap* JetUtilsTypeSignatureMap::getPrintTypeSignatureMap() {
    auto printVarArgMap = new FunctionVarArgTypeSignatureMap(
            FunctionIdGenerator::getNameFromId(JetUtilsTypeSignatureMap::getPrintTypeSignatureKey())
    );
    printVarArgMap->addFunctionVarArgTypeSignature(
            JetUtilsTypeSignatureMap::getPrintTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getPrintTypeSignature()
    );
    return printVarArgMap;
}

std::string JetUtilsTypeSignatureMap::getPrintTypeSignatureKey() {
    return FunctionIdGenerator::generateFor("print", "_vararg");
}

std::string JetUtilsTypeSignatureMap::getRangeTypeSignatureKey() {
    return FunctionIdGenerator::generateFor("range", "_int");
}

std::string JetUtilsTypeSignatureMap::getRange2pTypeSignatureKey() {
    return FunctionIdGenerator::generateFor("range", "_int_int");
}

std::string JetUtilsTypeSignatureMap::getRange3pTypeSignatureKey() {
    return FunctionIdGenerator::generateFor("range", "_int_int_int");
}

std::string JetUtilsTypeSignatureMap::getAssertTypeSignatureKey() {
    return FunctionIdGenerator::generateFor("assert", "_bool");
}

std::string JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignatureKey() {
    return FunctionIdGenerator::generateFor("assert", "_bool_string");
}

bool JetUtilsTypeSignatureMap::doesIdConflict(std::string id) {
    return id == JetUtilsTypeSignatureMap::getPrintTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getRange2pTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getRange3pTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getRangeTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getAssertTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignatureKey();

}

ProcedureTypeSignature* JetUtilsTypeSignatureMap::getPrintTypeSignature() {
    auto parameterList = new ParameterListTypeSignature();
    parameterList->markAsVariableLength(0, new ParameterListItemTypeSignature("value", new LiteralTypeSignature()));
    auto printTypeSignature = new ProcedureTypeSignature(parameterList);
    printTypeSignature->markAsBuiltIn();
    return printTypeSignature;
}

FunctionTypeSignature* JetUtilsTypeSignatureMap::getRangeTypeSignature() {
    auto rangeTypeSignature = new FunctionTypeSignature(
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("end", new IntLiteralTypeSignature())
            }),
            new ArrayTypeSignature(new IntLiteralTypeSignature())
    );
    rangeTypeSignature->markAsBuiltIn();
    return rangeTypeSignature;
}

FunctionTypeSignature* JetUtilsTypeSignatureMap::getRange2pTypeSignature() {
    auto rangeTypeSignature = new FunctionTypeSignature(
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("start", new IntLiteralTypeSignature()),
                new ParameterListItemTypeSignature("end", new IntLiteralTypeSignature())
            }),
            new ArrayTypeSignature(new IntLiteralTypeSignature())
    );
    rangeTypeSignature->markAsBuiltIn();
    return rangeTypeSignature;
}

FunctionTypeSignature* JetUtilsTypeSignatureMap::getRange3pTypeSignature() {
    auto rangeTypeSignature = new FunctionTypeSignature(
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("start", new IntLiteralTypeSignature()),
                new ParameterListItemTypeSignature("end", new IntLiteralTypeSignature()),
                new ParameterListItemTypeSignature("step", new IntLiteralTypeSignature())
            }),
            new ArrayTypeSignature(new IntLiteralTypeSignature())
    );
    rangeTypeSignature->markAsBuiltIn();
    return rangeTypeSignature;
}

FunctionTypeSignature* JetUtilsTypeSignatureMap::getAssertTypeSignature() {
    auto assertTypeSignature = new FunctionTypeSignature(
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("value", new BoolLiteralTypeSignature())
            }),
            new VoidTypeSignature()
    );
    assertTypeSignature->markAsBuiltIn();
    return assertTypeSignature;
}

FunctionTypeSignature* JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignature() {
    auto assertWithMessageTypeSignature = new FunctionTypeSignature(
            new ParameterListTypeSignature({
               new ParameterListItemTypeSignature("value", new BoolLiteralTypeSignature()),
               new ParameterListItemTypeSignature("message", new StringLiteralTypeSignature())
            }),
            new VoidTypeSignature()
    );
    assertWithMessageTypeSignature->markAsBuiltIn();
    return assertWithMessageTypeSignature;
}