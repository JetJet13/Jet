//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_LITERAL_EXPRESSION_IR_STRATEGY_H
#define JETLANG_LITERAL_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

class LiteralExpressionIRStrategy {
private:
    std::shared_ptr<IRInstructionNode> generateArrayAllocation(std::shared_ptr<IRStringLiteralNode> irStringLiteralNode, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
public:
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTLiteralExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_LITERAL_EXPRESSION_IR_STRATEGY_H
