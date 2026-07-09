//
// Created by Johny Georges on 2025-06-21.
//

#ifndef JETLANG_DREF_IR_INJECTOR_HELPER_H
#define JETLANG_DREF_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"

class DrefIRInjectorHelper {
public:
    static llvm::Value* inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_DREF_IR_INJECTOR_HELPER_H
