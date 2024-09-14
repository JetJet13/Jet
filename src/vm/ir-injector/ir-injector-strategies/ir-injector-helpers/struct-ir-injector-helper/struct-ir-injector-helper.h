//
// Created by Johny Georges on 2024-09-14.
//

#ifndef JETLANG_STRUCT_IR_INJECTOR_HELPER_H
#define JETLANG_STRUCT_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-load-instruction-node.h"
#include "../../../../ir-nodes/ir-instruction-node.h"

class StructIRInjectorHelper {
public:
    static IRLoadInstructionNode* injectStruct(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* structAllocation);
};

#endif //JETLANG_STRUCT_IR_INJECTOR_HELPER_H
