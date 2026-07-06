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
    std::shared_ptr<IRBlockNode> setupBlock(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<ASTControlFlowBlockNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTIfStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_IF_STATEMENT_IR_STRATEGY_H
