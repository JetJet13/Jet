//
// Created by Johny Georges on 2026-01-17.
//

#ifndef JETLANG_IR_CORE_INTERNAL_MODULE_H
#define JETLANG_IR_CORE_INTERNAL_MODULE_H

#include <memory>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-module-node.h"

class IRCoreInternalModule {
public:
    static std::shared_ptr<IRModuleNode> generate(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context);
};

#endif //JETLANG_IR_CORE_INTERNAL_MODULE_H
