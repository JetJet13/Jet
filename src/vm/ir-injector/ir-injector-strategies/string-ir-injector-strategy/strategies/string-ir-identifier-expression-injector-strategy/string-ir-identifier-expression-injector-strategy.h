//
// Created by Johny Georges on 2025-04-26.
//

#ifndef JETLANG_STRING_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_STRING_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"

class StringIRIdentifierExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_STRING_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H
