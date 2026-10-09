//
// Created by Johny Georges on 2026-01-10.
//

#include "ir-debug-internal-module.h"
#include "../../../../core/pre-processor/semantic-analyzer/jet-debug-type-signature-map/jet-debug-type-signature-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../ir-util-functions/assert-ir-function/assert-ir-function.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"

void IRDebugInternalModule::augment(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> coreIRModule) {
    AssertIRFunction::generateAssertDebugGlobals(irGenerator, context, coreIRModule);
    AssertIRFunction::generateAssertDebugRefCountFunction(irGenerator, context, coreIRModule);
    AssertIRFunction::generateAssertDebugStructRefCountFunction(irGenerator, context, coreIRModule);
    AssertIRFunction::generateAssertDebugLambdaRefCountFunction(irGenerator, context, coreIRModule);
}

std::string IRDebugInternalModule::getIRName(std::string id) {
    auto name = FunctionIdGenerator::getNameFromId(id);
    if (name == JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignatureKey()) {
        return AssertIRFunction::getAssertDebugRefCountIRFunctionName();
    }

    if (name == JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignatureKey() ||
        name == JetDebugTypeSignatureMap::getAssertDebugTupleRefCountTypeSignatureKey() ||
        name == JetDebugTypeSignatureMap::getAssertDebugClassRefCountTypeSignatureKey()) {
        // we re-use the struct-ref function for tuples and class instances because
        // they share the same data structure in the backend
        return AssertIRFunction::getAssertDebugStructRefCountIRFunctionName();
    } else if (name == JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignatureKey()) {
        return AssertIRFunction::getAssertDebugLambdaRefCountIRFunctionName();
    }
    throw std::logic_error("unable to find debug internal function name");
}