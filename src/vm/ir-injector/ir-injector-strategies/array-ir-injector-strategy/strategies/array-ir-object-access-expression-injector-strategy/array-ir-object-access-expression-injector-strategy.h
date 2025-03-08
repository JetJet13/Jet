//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_ARRAY_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_ARRAY_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"

class ArrayIRObjectAccessExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
    llvm::Value* injectRef(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
    llvm::Value* injectOperand(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_ARRAY_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
