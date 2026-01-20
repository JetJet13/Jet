//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_STRUCT_IR_ARRAY_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_STRUCT_IR_ARRAY_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"

class StructIRArrayAccessExpressionInjectorStrategy {
private:
    llvm::Value* getPointerAtIndex(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};


#endif //JETLANG_STRUCT_IR_ARRAY_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
