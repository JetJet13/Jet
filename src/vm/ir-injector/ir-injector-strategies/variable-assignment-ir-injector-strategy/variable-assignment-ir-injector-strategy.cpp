//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"

void VariableAssignmentIRInjectorStrategy::inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope) {
    Logger::log("Var Assignment", irVariableAssignmentStatement->getVariableName());
    auto irExpressionValue = irInjectorMap->getInjector(irVariableAssignmentStatement->getIRExpression()->getTypeSignature())
            ->inject(
                    irVariableAssignmentStatement->getIRExpression(),
                    builder,
                    irInjectorMap,
                    IR_OPERAND_OP, irModule, scope);
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    if (globalVariable) {
        builder->get()->CreateStore(
            irExpressionValue,
            globalVariable.value()->getValue()
        );
    } else {
        builder->get()->CreateStore(
            irExpressionValue,
            scope->find(irVariableAssignmentStatement->getVariableName()).value()->getValue()
        );
    }
}