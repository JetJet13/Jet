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
#include "../../../ir-injector-map.h"

class StructIRInjectorHelper {
public:
    static llvm::Value* injectStructCopy(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* structAllocation, IRModuleNode* irModule);
    static llvm::Value* injectStructCopy(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRStructType* irStructType, llvm::Value* structSource, IRModuleNode* irModule);
};

#endif //JETLANG_STRUCT_IR_INJECTOR_HELPER_H
