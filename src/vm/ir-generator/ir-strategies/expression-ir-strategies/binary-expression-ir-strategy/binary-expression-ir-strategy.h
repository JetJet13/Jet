//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-expression-node.h"
#include "../../../../../core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-comparator-expression-node.h"

class BinaryExpressionIRStrategy {
private:
    llvm::Instruction::BinaryOps determineArithmeticOperatorIR(ASTBinaryArithmeticOperatorNode* operatorNode, TypeSignature* typeSignature);
    llvm::CmpInst::Predicate determineComparatorPredicate(ASTBinaryComparatorOperatorNode* operatorNode, TypeSignature* typeSignature);
public:
    IRBinaryExpressionNode* generate(ASTBinaryArithmeticExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
    IRBinaryExpressionNode* generate(ASTBinaryComparatorExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_BINARY_EXPRESSION_IR_STRATEGY_H
