//
// Created by Johny Georges on 2024-10-21.
//

#include "ir-util-internal-module.h"
#include "../../ir-util-functions/print-ir-function/print-ir-function.h"

IRModuleNode* IRUtilInternalModule::generate(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context) {
    auto irModule = irGenerator->generateModule("jet-util");
    irGenerator->initModule(irModule);
    PrintIRFunction::generatePrintFunction(irGenerator, context, irModule);
    return irModule;
}