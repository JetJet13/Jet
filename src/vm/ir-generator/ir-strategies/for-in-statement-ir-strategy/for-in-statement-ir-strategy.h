//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_FOR_IN_STATEMENT_IR_STRATEGY_H
#define JETLANG_FOR_IN_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"

class ForInStatementIRStrategy {
public:
    IRStatementNode* generate(ASTForInStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_FOR_IN_STATEMENT_IR_STRATEGY_H
