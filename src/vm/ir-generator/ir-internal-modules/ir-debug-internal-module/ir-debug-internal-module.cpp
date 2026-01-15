//
// Created by Johny Georges on 2026-01-10.
//

#include "ir-debug-internal-module.h"
#include "../../../../core/pre-processor/semantic-analyzer/jet-debug-type-signature-map/jet-debug-type-signature-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../ir-util-functions/assert-ir-function/assert-ir-function.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"

IRModuleNode* IRDebugInternalModule::generate(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context) {
    auto irModule = irGenerator->generateModule("jet-debug");
    irGenerator->initModule(irModule);
    AssertIRFunction::generateAssertDebugGlobals(irGenerator, context, irModule);
    AssertIRFunction::generateAssertDebugRefCountFunction(irGenerator, context, irModule);
    AssertIRFunction::generateAssertDebugStructRefCountFunction(irGenerator, context, irModule);
    AssertIRFunction::generateAssertDebugLambdaRefCountFunction(irGenerator, context, irModule);
    return irModule;
}

std::string IRDebugInternalModule::getIRName(std::string id) {
    auto name = FunctionIdGenerator::getNameFromId(id);
    if (name == JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignatureKey()) {
        return AssertIRFunction::getAssertDebugRefCountIRFunctionName();
    }

    if (name == JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignatureKey()) {
        return AssertIRFunction::getAssertDebugStructRefCountIRFunctionName();
    } else if (name == JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignatureKey()) {
        return AssertIRFunction::getAssertDebugLambdaRefCountIRFunctionName();
    }
    throw std::logic_error("unable to find debug internal function name");
}