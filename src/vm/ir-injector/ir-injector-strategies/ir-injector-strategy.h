//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_IR_INJECTOR_STRATEGY_H
#define JETLANG_IR_INJECTOR_STRATEGY_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"
#include "../../types/ir-operation-type.h"
#include "../../ir-nodes/ir-module-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../ir-injector.h"

class IRInjectorStrategy {
public:
    virtual llvm::Value* inject(std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) = 0;
};

#endif //JETLANG_IR_INJECTOR_STRATEGY_H
