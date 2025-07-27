//
// Created by Johny Georges on 2024-10-21.
//

#include "ir-util-internal-module.h"
#include "../../ir-util-functions/print-ir-function/print-ir-function.h"
#include "../../ir-util-functions/range-ir-function/range-ir-function.h"
#include "../../../../core/pre-processor/semantic-analyzer/jet-utils-type-signature-map/jet-utils-type-signature-map.h"

IRModuleNode* IRUtilInternalModule::generate(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context) {
    auto irModule = irGenerator->generateModule("jet-util");
    irGenerator->initModule(irModule);
    RangeIRFunction::generateRange3pFunction(irGenerator, context, irModule);
    RangeIRFunction::generateRange2pFunction(irGenerator, context, irModule);
    RangeIRFunction::generateRange1pFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintIntFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintFloatFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintCharFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintBoolFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintStringFunction(irGenerator, context, irModule);
    PrintIRFunction::generatePrintFunction(irGenerator, context, irModule);
    return irModule;
}

std::string IRUtilInternalModule::getIRName(std::string id, ASTFunctionArgumentListNode* argumentList) {
    if (id == JetUtilsTypeSignatureMap::getPrintTypeSignatureKey()) {
        return PrintIRFunction::getPrintIRFunctionName();
    }

    if (id == JetUtilsTypeSignatureMap::getRangeTypeSignatureKey()) {
        if (argumentList->numArguments() == 1) {
            return RangeIRFunction::getRange1pIRFunctionName();
        } else if (argumentList->numArguments() == 2) {
            return RangeIRFunction::getRange2pIRFunctionName();
        } else if (argumentList->numArguments() == 3) {
            return RangeIRFunction::getRange3pIRFunctionName();
        }
    }
    throw std::logic_error("unable to find util internal function name");
}