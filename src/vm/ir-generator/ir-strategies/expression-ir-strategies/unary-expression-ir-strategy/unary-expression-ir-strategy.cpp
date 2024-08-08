//
// Created by Johny Georges on 2024-06-25.
//

#include "unary-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-negate-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-arithmetic-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRUnaryExpressionNode* UnaryExpressionIRStrategy::generate(ASTUnaryExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto expressionIr = irGenerator->generateFor(node->getExpressionNode(), scope, irModule);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generatePointerType(irType));
    if (node->getUnaryOperatorNode()->isPlus()) {
        return new IRUnaryArithmeticExpressionNode(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                llvm::ConstantInt::get(**context, llvm::APInt(32, 1)),
                expressionIr->getValue()
        ), expressionIr, irType, sourceAllocation);
    } else if (node->getUnaryOperatorNode()->isMinus()) {
        return new IRUnaryArithmeticExpressionNode(node, llvm::BinaryOperator::Create(
                llvm::Instruction::BinaryOps::Mul,
                llvm::ConstantInt::get(**context, llvm::APInt(32, -1, true)),
                expressionIr->getValue()
        ), expressionIr, irType, sourceAllocation);
    } else {
        return new IRUnaryNegateExpressionNode(node, llvm::UnaryOperator::Create(
                llvm::Instruction::UnaryOps::FNeg,
                expressionIr->getValue()
        ), expressionIr, irType, sourceAllocation);
    }
}