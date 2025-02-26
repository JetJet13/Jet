//
// Created by Johny Georges on 2024-09-14.
//

#ifndef JETLANG_STRUCT_IR_INJECTOR_HELPER_H
#define JETLANG_STRUCT_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-load-instruction-node.h"
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-injector.h"

class StructIRInjectorHelper {
public:
    static llvm::Value* injectStructCopy(IRBlockNode* irBlock, IRInstructionNode* structAllocation, IRModuleNode* irModule, IROperationType irOperationType);
    static llvm::Value* injectStructCopy(IRBlockNode* irBlock, IRStructType* irStructType, llvm::Value* structSource, IRModuleNode* irModule, IROperationType irOperationType);
};

#endif //JETLANG_STRUCT_IR_INJECTOR_HELPER_H
