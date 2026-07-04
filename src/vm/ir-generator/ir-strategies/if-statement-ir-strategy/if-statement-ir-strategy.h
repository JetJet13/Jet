//
// Created by Johny Georges on 2025-01-08.
//

#ifndef JETLANG_IF_STATEMENT_IR_STRATEGY_H
#define JETLANG_IF_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"

class IfStatementIRStrategy {
private:
    IRBlockNode* setupBlock(IRBlockNode* irBlockNode, std::shared_ptr<ASTControlFlowBlockNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
public:
    IRStatementNode* generate(std::shared_ptr<ASTIfStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_IF_STATEMENT_IR_STRATEGY_H
