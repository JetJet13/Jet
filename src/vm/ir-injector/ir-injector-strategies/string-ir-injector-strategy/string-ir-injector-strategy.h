//
// Created by Johny Georges on 2024-08-12.
//

#ifndef JETLANG_STRING_IR_INJECTOR_STRATEGY_H
#define JETLANG_STRING_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-aggregate-identifier-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "strategies/string-ir-string-literal-expression-injector-strategy/string-ir-string-literal-expression-injector-strategy.h"
#include "strategies/string-ir-object-access-expression-injector-strategy/string-ir-object-access-expression-injector-strategy.h"
#include "strategies/string-ir-array-access-expression-injector-strategy/string-ir-array-access-expression-injector-strategy.h"
#include "strategies/string-ir-tuple-access-expression-injector-strategy/string-ir-tuple-access-expression-injector-strategy.h"
#include "strategies/string-ir-class-property-access-expression-injector-strategy/string-ir-class-property-access-expression-injector-strategy.h"
#include "strategies/string-ir-dref-expression-injector-strategy/string-ir-dref-expression-injector-strategy.h"
#include "strategies/string-ir-identifier-expression-injector-strategy/string-ir-identifier-expression-injector-strategy.h"
#include "strategies/string-ir-concat-expression-injector-strategy/string-ir-concat-expression-injector-strategy.h"


class StringIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
private:
    StringIRStringLiteralExpressionInjectorStrategy _stringIRStringLiteralExpressionInjectorStrategy = StringIRStringLiteralExpressionInjectorStrategy();
    StringIRObjectAccessExpressionInjectorStrategy _stringIRObjectAccessExpressionInjectorStrategy = StringIRObjectAccessExpressionInjectorStrategy();
    StringIRArrayAccessExpressionInjectorStrategy _stringIRArrayAccessExpressionInjectorStrategy = StringIRArrayAccessExpressionInjectorStrategy();
    StringIRTupleAccessExpressionInjectorStrategy _stringIRTupleAccessExpressionInjectorStrategy = StringIRTupleAccessExpressionInjectorStrategy();
    StringIRDrefExpressionInjectorStrategy _stringIRDrefExpressionInjectorStrategy = StringIRDrefExpressionInjectorStrategy();
    StringIRIdentifierExpressionInjectorStrategy _stringIRIdentifierExpressionInjectorStrategy = StringIRIdentifierExpressionInjectorStrategy();
    StringIRConcatExpressionInjectorStrategy _stringIRConcatExpressionInjectorStrategy = StringIRConcatExpressionInjectorStrategy();
    StringIRClassPropertyAccessExpressionInjectorStrategy _stringIRClassPropertyAccessExpressionInjectorStrategy = StringIRClassPropertyAccessExpressionInjectorStrategy();
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_STRING_IR_INJECTOR_STRATEGY_H
