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
    return "range";
}

std::string JetUtilsTypeSignatureMap::getRange2pTypeSignatureKey() {
    return "range";
}

std::string JetUtilsTypeSignatureMap::getRange3pTypeSignatureKey() {
    return "range";
}

std::string JetUtilsTypeSignatureMap::getAssertTypeSignatureKey() {
    return "assert";
}

std::string JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignatureKey() {
    return "assert";
}

bool JetUtilsTypeSignatureMap::doesIdConflict(std::string id) {
    return id == JetUtilsTypeSignatureMap::getPrintTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getRange2pTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getRange3pTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getRangeTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getAssertTypeSignatureKey()
            || id == JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignatureKey();

}

std::shared_ptr<ProcedureTypeSignature> JetUtilsTypeSignatureMap::getPrintTypeSignature() {
    auto parameterList = std::make_shared<ParameterListTypeSignature>();
    parameterList->markAsVariableLength(0, std::make_shared<ParameterListItemTypeSignature>("value", std::make_shared<LiteralTypeSignature>()));
    auto printTypeSignature = std::make_shared<ProcedureTypeSignature>(parameterList);
    printTypeSignature->markAsBuiltIn(BI_PRINT_TYPE_SOURCE);
    return printTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetUtilsTypeSignatureMap::getRangeTypeSignature() {
    auto rangeTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>(std::vector {
                std::make_shared<ParameterListItemTypeSignature>("end", std::make_shared<IntLiteralTypeSignature>())
            }),
            std::make_shared<ArrayTypeSignature>(std::make_shared<IntLiteralTypeSignature>())
    );
    rangeTypeSignature->markAsBuiltIn(BI_RANGE_TYPE_SOURCE);
    return rangeTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetUtilsTypeSignatureMap::getRange2pTypeSignature() {
    auto rangeTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>( std::vector {
                std::make_shared<ParameterListItemTypeSignature>("start", std::make_shared<IntLiteralTypeSignature>()),
                std::make_shared<ParameterListItemTypeSignature>("end", std::make_shared<IntLiteralTypeSignature>())
            }),
            std::make_shared<ArrayTypeSignature>(std::make_shared<IntLiteralTypeSignature>())
    );
    rangeTypeSignature->markAsBuiltIn(BI_RANGE_2P_TYPE_SOURCE);
    return rangeTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetUtilsTypeSignatureMap::getRange3pTypeSignature() {
    auto rangeTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>(std::vector {
                std::make_shared<ParameterListItemTypeSignature>("start", std::make_shared<IntLiteralTypeSignature>()),
                std::make_shared<ParameterListItemTypeSignature>("end", std::make_shared<IntLiteralTypeSignature>()),
                std::make_shared<ParameterListItemTypeSignature>("step", std::make_shared<IntLiteralTypeSignature>())
            }),
            std::make_shared<ArrayTypeSignature>(std::make_shared<IntLiteralTypeSignature>())
    );
    rangeTypeSignature->markAsBuiltIn(BI_RANGE_3P_TYPE_SOURCE);
    return rangeTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetUtilsTypeSignatureMap::getAssertTypeSignature() {
    auto assertTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>(std::vector {
                std::make_shared<ParameterListItemTypeSignature>("value", std::make_shared<BoolLiteralTypeSignature>())
            }),
            std::make_shared<VoidTypeSignature>()
    );
    assertTypeSignature->markAsBuiltIn(BI_ASSERT_TYPE_SOURCE);
    return assertTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignature() {
    auto assertWithMessageTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>(std::vector {
               std::make_shared<ParameterListItemTypeSignature>("value", std::make_shared<BoolLiteralTypeSignature>()),
               std::make_shared<ParameterListItemTypeSignature>("message", std::make_shared<StringLiteralTypeSignature>())
            }),
            std::make_shared<VoidTypeSignature>()
    );
    assertWithMessageTypeSignature->markAsBuiltIn(BI_ASSERT_WITH_MESSAGE_TYPE_SOURCE);
    return assertWithMessageTypeSignature;
}