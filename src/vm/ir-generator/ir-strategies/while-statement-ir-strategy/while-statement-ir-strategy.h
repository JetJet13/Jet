//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_WHILE_STATEMENT_IR_STRATEGY_H
#define JETLANG_WHILE_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"

class WhileStatementIRStrategy {
private:
    IRBlockNode* setupBlock(IRBlockNode* irBlockNode, std::shared_ptr<ASTControlFlowBlockNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
public:
    IRStatementNode* generate(std::shared_ptr<ASTWhileStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_WHILE_STATEMENT_IR_STRATEGY_H
