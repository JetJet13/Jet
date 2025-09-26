//
// Created by Johny Georges on 2025-02-18.
//

#include "enum-ir-injector-strategy.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"

llvm::Value* EnumIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return irExpression->getValue();
    }
    throw std::logic_error("EnumIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}
