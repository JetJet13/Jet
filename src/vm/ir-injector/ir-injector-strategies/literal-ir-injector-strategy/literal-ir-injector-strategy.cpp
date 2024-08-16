//
// Created by Johny Georges on 2024-08-14.
//

#include "literal-ir-injector-strategy.h"

llvm::Value* LiteralIRInjectorStrategy::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    if (irExpression->is(IR_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRLiteralExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->inject((IRBinaryArithmeticExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_BINARY_COMPARISON_EXPRESSION_NODE)) {
        return this->inject((IRBinaryArithmeticExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_UNARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->inject((IRBinaryArithmeticExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_LOGICAL_EXPRESSION_NODE)) {
        return this->inject((IRLogicalExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap);
    } else if (irExpression->is(IR_UNARY_EXPRESSION_NODE)) {
        return this->inject((IRUnaryExpressionNode*)irExpression, builder, irInjectorMap);
    }
    throw std::logic_error("LiteralIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return builder->get()->CreateLoad(irExpression->getType(), irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(
            irExpression->getSource()->getType(),
            irExpression->getSource()->getValue(),
            { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() }
    );
    builder->get()->Insert(pointer);
    return builder->get()->CreateLoad(irExpression->getType(), pointer);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRBinaryArithmeticExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRBinaryComparisonExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRUnaryArithmeticExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRLogicalExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRUnaryExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap) {
    return irExpression->getValue();
}