//
// Created by Johny Georges on 2026-01-10.
//

#ifndef JETLANG_IR_DEBUG_INTERNAL_MODULE_H
#define JETLANG_IR_DEBUG_INTERNAL_MODULE_H

#include <memory>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-module-node.h"

class IRDebugInternalModule {
public:
    static void augment(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> coreIRModule);
    static std::string getIRName(std::string id);
};

#endif //JETLANG_IR_DEBUG_INTERNAL_MODULE_H
