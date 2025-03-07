//
// Created by Johny Georges on 2025-03-03.
//

#ifndef JETLANG_REF_IR_INJECTOR_HELPER_H
#define JETLANG_REF_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-injector.h"

class RefIRInjectorHelper {
public:
    static llvm::Value* injectRefSource(IRBlockNode* irBlock, IRExpressionNode* irExpression, llvm::Value* irValue, IRModuleNode* irModule, IROperationType irOperationType);
};


#endif //JETLANG_REF_IR_INJECTOR_HELPER_H
