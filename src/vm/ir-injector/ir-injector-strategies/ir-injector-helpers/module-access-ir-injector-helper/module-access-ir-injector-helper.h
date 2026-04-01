//
// Created by Johny Georges on 2026-03-27.
//

#ifndef JETLANG_MODULE_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_MODULE_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-module-access-expression-node.h"

class ModuleAccessIRInjectorHelper {
public:
    static llvm::Value* inject(IRModuleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation);
};

#endif //JETLANG_MODULE_ACCESS_IR_INJECTOR_HELPER_H
