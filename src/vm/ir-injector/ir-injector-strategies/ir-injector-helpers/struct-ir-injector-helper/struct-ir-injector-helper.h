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
#include "../../../../ir-type/ir-struct-ref-type.h"

class StructIRInjectorHelper {
public:
    static llvm::Value* injectStructRef(IRBlockNode* irBlock, IRInstructionNode* structRefAllocation, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector);
    static llvm::Value* injectStructRefCopy(IRBlockNode* irBlock, IRStructRefType* irStructRefType, llvm::Value* structRefSource, std::shared_ptr<IRModuleNode> irModule, IRInjector* irInjector);
};

#endif //JETLANG_STRUCT_IR_INJECTOR_HELPER_H
