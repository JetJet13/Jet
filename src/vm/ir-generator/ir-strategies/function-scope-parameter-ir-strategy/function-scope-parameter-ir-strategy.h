//
// Created by Johny Georges on 2024-11-16.
//

#ifndef JETLANG_FUNCTION_SCOPE_PARAMETER_IR_STRATEGY_H
#define JETLANG_FUNCTION_SCOPE_PARAMETER_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

class FunctionScopeParameterIRStrategy {
public:
    void generate(ParameterListItemTypeSignature* scopeParameter, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_FUNCTION_SCOPE_PARAMETER_IR_STRATEGY_H
