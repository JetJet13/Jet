//
// Created by Johny Georges on 2024-10-21.
//

#include "ir-util-internal-module.h"
#include "../../ir-util-functions/print-ir-function/print-ir-function.h"
#include "../../ir-util-functions/range-ir-function/range-ir-function.h"
#include "../../../../core/pre-processor/semantic-analyzer/jet-utils-type-signature-map/jet-utils-type-signature-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../ir-util-functions/assert-ir-function/assert-ir-function.h"

void IRUtilInternalModule::augment(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> coreIrModule) {
    PrintIRFunction::generatePrintGlobals(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintRefFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintArrayFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintStructFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::declarePrintStructRefFunction(irGenerator, context, coreIrModule);

    PrintIRFunction::generatePrintIntFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintFloatFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintCharFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintBoolFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintStringFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintRefFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintArrayFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintStructFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintStructRefFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintLambdaFunction(irGenerator, context, coreIrModule);
    PrintIRFunction::generatePrintFunction(irGenerator, context, coreIrModule);
    RangeIRFunction::generateRange3pFunction(irGenerator, context, coreIrModule);
    RangeIRFunction::generateRange2pFunction(irGenerator, context, coreIrModule);
    RangeIRFunction::generateRange1pFunction(irGenerator, context, coreIrModule);
    AssertIRFunction::generateAssertGlobals(irGenerator, context, coreIrModule);
    AssertIRFunction::generateAssertFunction(irGenerator, context, coreIrModule);
    AssertIRFunction::generateAssertWithMessageFunction(irGenerator, context, coreIrModule);
}

std::string IRUtilInternalModule::getIRName(std::string id) {
    if (id == JetUtilsTypeSignatureMap::getPrintTypeSignatureKey()) {
        return PrintIRFunction::getPrintIRFunctionName();
    }

    if (id == JetUtilsTypeSignatureMap::getRangeTypeSignatureKey()) {
        return RangeIRFunction::getRange1pIRFunctionName();
    } else if (id == JetUtilsTypeSignatureMap::getRange2pTypeSignatureKey()) {
        return RangeIRFunction::getRange2pIRFunctionName();
    } else if (id == JetUtilsTypeSignatureMap::getRange3pTypeSignatureKey()) {
        return RangeIRFunction::getRange3pIRFunctionName();
    }

    if (id == JetUtilsTypeSignatureMap::getAssertTypeSignatureKey()) {
        return AssertIRFunction::getAssertIRFunctionName();
    } else if (id == JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignatureKey()) {
        return AssertIRFunction::getAssertWithMessageIRFunctionName();
    }
    throw std::logic_error("unable to find util internal function name");
}