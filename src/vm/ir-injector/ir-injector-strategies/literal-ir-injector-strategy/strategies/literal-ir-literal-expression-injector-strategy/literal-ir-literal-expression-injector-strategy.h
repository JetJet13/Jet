//
// Created by Johny Georges on 2025-07-28.
//

#ifndef JETLANG_LITERAL_IR_LITERAL_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_LITERAL_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"

class LiteralIRLiteralExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    llvm::Value* injectRef(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    llvm::Value* injectOperand(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
public:
    llvm::Value* inject(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_LITERAL_IR_LITERAL_EXPRESSION_INJECTOR_STRATEGY_H
