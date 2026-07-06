//
// Created by Johny Georges on 2025-03-15.
//

#ifndef JETLANG_POINTER_IR_REF_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_POINTER_IR_REF_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-ref-expression-node.h"

class PointerIRRefExpressionInjectorStrategy {
private:
    llvm::Value* injectRawValue(std::shared_ptr<IRRefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
public:
    llvm::Value* inject(std::shared_ptr<IRRefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_POINTER_IR_REF_EXPRESSION_INJECTOR_STRATEGY_H
