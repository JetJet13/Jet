//
// Created by Johny Georges on 2024-08-14.
//

#ifndef JETLANG_LITERAL_IR_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-arithmetic-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-comparison-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-arithmetic-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-logical-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-negate-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-method-invocation-expression-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-ref-expression-node.h"
#include "strategies/literal-ir-identifier-expression-injector-strategy/literal-ir-identifier-expression-injector-strategy.h"
#include "strategies/literal-ir-object-access-expression-injector-strategy/literal-ir-object-access-expression-injector-strategy.h"
#include "strategies/literal-ir-binary-arithmetic-expression-injector-strategy/literal-ir-binary-arithmetic-expression-injector-strategy.h"
#include "strategies/literal-ir-binary-comparison-expression-injector-strategy/literal-ir-binary-comparison-expression-injector-strategy.h"
#include "strategies/literal-ir-unary-arithmetic-expression-injector-strategy/literal-ir-unary-arithmetic-expression-injector-strategy.h"
#include "strategies/literal-ir-unary-negate-expression-injector-strategy/literal-ir-unary-negate-expression-injector-strategy.h"
#include "strategies/literal-ir-logical-expression-injector-strategy/literal-ir-logical-expression-injector-strategy.h"
#include "strategies/literal-ir-array-access-expression-injector-strategy/literal-ir-array-access-expression-injector-strategy.h"
#include "strategies/literal-ir-tuple-access-expression-injector-strategy/literal-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/literal-ir-dref-expression-injector-strategy/literal-ir-dref-expression-injector-strategy.h"
#include "strategies/literal-ir-literal-expression-injector-strategy/literal-ir-literal-expression-injector-strategy.h"

class LiteralIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    LiteralIRIdentifierExpressionInjectorStrategy _identifierExpressionInjector = LiteralIRIdentifierExpressionInjectorStrategy();
    LiteralIRLiteralExpressionInjectorStrategy _literalExpressionInjector = LiteralIRLiteralExpressionInjectorStrategy();
    LiteralIRObjectAccessExpressionInjectorStrategy _objectAccessExpressionInjector = LiteralIRObjectAccessExpressionInjectorStrategy();
    LiteralIRBinaryArithmeticExpressionInjectorStrategy _binaryArithmeticExpressionInjector = LiteralIRBinaryArithmeticExpressionInjectorStrategy();
    LiteralIRBinaryComparisonExpressionInjectorStrategy _binaryComparisonExpressionInjector = LiteralIRBinaryComparisonExpressionInjectorStrategy();
    LiteralIRUnaryArithmeticExpressionInjectorStrategy _unaryArithmeticExpressionInjector = LiteralIRUnaryArithmeticExpressionInjectorStrategy();
    LiteralIRUnaryNegateExpressionInjectorStrategy _unaryNegateExpressionInjector = LiteralIRUnaryNegateExpressionInjectorStrategy();
    LiteralIRLogicalExpressionInjectorStrategy _logicalExpressionInjector = LiteralIRLogicalExpressionInjectorStrategy();
    LiteralIRArrayAccessExpressionInjectorStrategy _arrayAccessExpressionInjector = LiteralIRArrayAccessExpressionInjectorStrategy();
    LiteralIRTupleAccessExpressionInjectorStrategy _tupleAccessExpressionInjector = LiteralIRTupleAccessExpressionInjectorStrategy();
    LiteralIRDrefExpressionInjectorStrategy _literalIRDrefExpressionInjectorStrategy = LiteralIRDrefExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_LITERAL_IR_INJECTOR_STRATEGY_H
