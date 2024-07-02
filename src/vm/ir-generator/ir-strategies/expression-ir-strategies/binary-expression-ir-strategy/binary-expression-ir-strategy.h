//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-expression-node.h"

class BinaryExpressionIRStrategy {
private:
    llvm::Instruction::BinaryOps determineArithmeticOperatorIR(ASTBinaryOperatorNode* operatorNode);
    llvm::CmpInst::Predicate determineComparatorPredicate(ASTBinaryOperatorNode* operatorNode);
public:
    IRBinaryExpressionNode* generate(ASTBinaryExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H
