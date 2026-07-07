//
// Created by Johny Georges on 2024-06-21.
//

#ifndef JETLANG_STRUCT_EXPRESSION_IR_STRATEGY_H
#define JETLANG_STRUCT_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-struct-expression-node.h"

class StructExpressionIRStrategy {
private:
    std::shared_ptr<IRInstructionNode> generateStructAllocation(std::shared_ptr<IRStructType> irType, std::unordered_map<std::string, std::shared_ptr<IRInstructionNode>> structValueSourceAllocationMap, IRGenerator* irGenerator, IRContext* irContext);
    std::shared_ptr<IRInstructionNode> generateStructRefAllocation(std::shared_ptr<ASTStructExpressionNode> node, std::shared_ptr<IRStructRefType> irType, IRGenerator* irGenerator, IRContext* irContext, std::shared_ptr<IROperation> irOperation);
public:
    std::shared_ptr<IRStructExpressionNode> generate(std::shared_ptr<ASTStructExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_STRUCT_EXPRESSION_IR_STRATEGY_H
