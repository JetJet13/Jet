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
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTForInStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_FOR_IN_STATEMENT_IR_STRATEGY_H
