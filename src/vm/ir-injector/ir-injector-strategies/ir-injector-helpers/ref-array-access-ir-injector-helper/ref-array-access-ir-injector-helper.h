//
// Created by Johny Georges on 2025-06-21.
//

#ifndef JETLANG_REF_ARRAY_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_REF_ARRAY_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-ref-array-access-expression-node.h"

class RefArrayAccessIRInjectorHelper {
public:
    static llvm::Value* inject(IRRefArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_REF_ARRAY_ACCESS_IR_INJECTOR_HELPER_H
