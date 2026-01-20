//
// Created by Johny Georges on 2024-10-21.
//

#ifndef JETLANG_IR_UTIL_INTERNAL_MODULE_H
#define JETLANG_IR_UTIL_INTERNAL_MODULE_H

#include <memory>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-module-node.h"

class IRUtilInternalModule {
public:
    static void augment(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> coreIrModule);
    static std::string getIRName(std::string id);
};

#endif //JETLANG_IR_UTIL_INTERNAL_MODULE_H
