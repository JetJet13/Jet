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
    IRInstructionNode* generateStructAllocation(ASTStructExpressionNode* node, IRStructType* irType, std::unordered_map<std::string, IRInstructionNode*> structValueSourceAllocationMap, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType);
public:
    IRStructExpressionNode* generate(ASTStructExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
};

#endif //JETLANG_STRUCT_EXPRESSION_IR_STRATEGY_H
