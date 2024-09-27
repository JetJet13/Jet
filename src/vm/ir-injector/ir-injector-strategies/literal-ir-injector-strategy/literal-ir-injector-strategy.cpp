//
// Created by Johny Georges on 2024-08-14.
//

#include "literal-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"

llvm::Value * LiteralIRInjectorStrategy::inject(IRExpressionNode *irExpression,
                                                std::unique_ptr<llvm::IRBuilder<>> *builder,
                                                IRInjectorMap *irInjectorMap,
                                                IROperationType irOperationType, IRModuleNode *irModule) {
    if (irExpression->is(IR_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRLiteralExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->inject((IRBinaryArithmeticExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_BINARY_COMPARISON_EXPRESSION_NODE)) {
        return this->inject((IRBinaryComparisonExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_UNARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->inject((IRUnaryArithmeticExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_UNARY_NEGATE_EXPRESSION_NODE)) {
        return this->inject((IRUnaryNegateExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_LOGICAL_EXPRESSION_NODE)) {
        return this->inject((IRLogicalExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    }
    throw std::logic_error("LiteralIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    return StructIRInjectorHelper::extractNestedStruct(builder, irExpression)->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRBinaryArithmeticExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {

    auto irLeftNodeValue = irInjectorMap->getInjector(irExpression->getLeftNode()->getTypeSignature())->inject(
            irExpression->getLeftNode(), builder, irInjectorMap, irOperationType, irModule);
    auto leftNodeValue = builder->get()->CreateLoad(irExpression->getLeftNode()->getIRType()->getType(), irLeftNodeValue);

    auto irRightNodeValue = irInjectorMap->getInjector(irExpression->getRightNode()->getTypeSignature())->inject(
            irExpression->getRightNode(), builder, irInjectorMap, irOperationType, irModule);
    auto rightNodeValue = builder->get()->CreateLoad(irExpression->getRightNode()->getIRType()->getType(), irRightNodeValue);

    return builder->get()->CreateBinOp(irExpression->getValue()->getOpcode(), leftNodeValue, rightNodeValue);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRBinaryComparisonExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {

    auto irLeftNodeValue = irInjectorMap->getInjector(irExpression->getLeftNode()->getTypeSignature())->inject(
            irExpression->getLeftNode(), builder, irInjectorMap, irOperationType, irModule);
    auto leftNodeValue = builder->get()->CreateLoad(irExpression->getLeftNode()->getIRType()->getType(), irLeftNodeValue);

    auto irRightNodeValue = irInjectorMap->getInjector(irExpression->getRightNode()->getTypeSignature())->inject(
            irExpression->getRightNode(), builder, irInjectorMap, irOperationType, irModule);
    auto rightNodeValue = builder->get()->CreateLoad(irExpression->getRightNode()->getIRType()->getType(), irRightNodeValue);

    return builder->get()->CreateCmp(irExpression->getValue()->getPredicate(), leftNodeValue, rightNodeValue);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRUnaryArithmeticExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    return builder->get()->Insert(irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRUnaryNegateExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    return builder->get()->Insert(irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRLogicalExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {

    auto irLeftNodeValue = irInjectorMap->getInjector(irExpression->getLeftNode()->getTypeSignature())->inject(
            irExpression->getLeftNode(), builder, irInjectorMap, irOperationType, irModule);
    auto leftNodeValue = builder->get()->CreateLoad(irExpression->getLeftNode()->getIRType()->getType(), irLeftNodeValue);

    auto irRightNodeValue = irInjectorMap->getInjector(irExpression->getRightNode()->getTypeSignature())->inject(
            irExpression->getRightNode(), builder, irInjectorMap, irOperationType, irModule);
    auto rightNodeValue = builder->get()->CreateLoad(irExpression->getRightNode()->getIRType()->getType(), irRightNodeValue);

    return builder->get()->CreateBinOp(irExpression->getValue()->getOpcode(), leftNodeValue, rightNodeValue);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto irSourceValue = irExpression->getSourceExpression()->getValue();
    auto irSourceType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto irIndexValue = irInjectorMap->getInjector(irExpression->getIndexExpression()->getTypeSignature())->inject(
            irExpression->getIndexExpression(), builder, irInjectorMap, irOperationType, irModule);
    builder->get()->CreateCall(irModule->getArrayAccessFunction(), { irIndexValue, irSourceValue });
    auto zeroIndex = builder->get()->getInt32(0);
    auto pointerIndex = builder->get()->getInt32(irSourceType->getPointerIndex());
    auto pointer = builder->get()->CreateInBoundsGEP(
            irExpression->getSourceExpression()->getIRType()->getSourceType()->getType(),
            irExpression->getSourceExpression()->getValue(),
            { zeroIndex, pointerIndex }
    );
    auto loadedPointer = builder->get()->CreateLoad(pointer->getType(), pointer);
    auto pointerAtIndex = builder->get()->CreateInBoundsGEP(
        irExpression->getIRType()->getSourceType()->getType(),
        loadedPointer,
        { irIndexValue }
    );
    return builder->get()->CreateLoad(
        irExpression->getIRType()->getSourceType()->getType(),
        pointerAtIndex
    );
}