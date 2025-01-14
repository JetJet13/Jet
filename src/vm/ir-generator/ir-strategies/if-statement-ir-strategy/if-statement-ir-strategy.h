//
// Created by Johny Georges on 2025-01-08.
//

#ifndef JETLANG_IF_STATEMENT_IR_STRATEGY_H
#define JETLANG_IF_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"

class IfStatementIRStrategy {
private:
    IRBlockNode* setupBlock(IRBlockNode* irBlockNode, ASTControlFlowBlockNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
public:
    IRStatementNode* generate(ASTIfStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_IF_STATEMENT_IR_STRATEGY_H
