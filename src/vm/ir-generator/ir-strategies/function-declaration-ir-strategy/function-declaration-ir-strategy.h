//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_FUNCTION_DECLARATION_IR_STRATEGY_H
#define JETLANG_FUNCTION_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"

class FunctionDeclarationIRStrategy {
public:
    IRFunctionDeclarationNode* generate(ASTFunctionDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_FUNCTION_DECLARATION_IR_STRATEGY_H
