//
// Created by Johny Georges on 2025-06-16.
//

#include "expression-statement-ir-injector-strategy.h"

void ExpressionStatementIRInjectorStrategy::inject(std::shared_ptr<IRExpressionStatementNode> irExpressionStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    irInjector->inject(irBlock, irExpressionStatement->getExpression(), std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope);
}