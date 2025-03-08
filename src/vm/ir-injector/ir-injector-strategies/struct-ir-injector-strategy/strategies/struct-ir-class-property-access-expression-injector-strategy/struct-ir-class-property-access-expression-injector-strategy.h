//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_STRUCT_IR_CLASS_PROPERTY_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_STRUCT_IR_CLASS_PROPERTY_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"

class StructIRClassPropertyAccessExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_TUPLE_IR_CLASS_PROPERTY_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
