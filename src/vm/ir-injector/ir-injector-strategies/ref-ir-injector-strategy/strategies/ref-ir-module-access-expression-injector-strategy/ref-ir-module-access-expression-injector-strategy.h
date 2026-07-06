//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_REF_IR_MODULE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_MODULE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-module-access-expression-node.h"

class RefIRModuleAccessExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    llvm::Value* injectOperand(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_REF_IR_MODULE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
