//
// Created by Johny Georges on 2025-03-24.
//

#ifndef JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H
#define JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-load-instruction-node.h"
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-injector.h"

class InstructionIRInjectorHelper {
public:
    static llvm::Value* inject(IRInstructionNode* irInstruction, IRBlockNode* irBlock, std::string name = "");
};

#endif //JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H
