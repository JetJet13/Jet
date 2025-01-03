//
// Created by Johny Georges on 2024-08-14.
//

#include "literal-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* LiteralIRInjectorStrategy::inject(IRExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRLiteralExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_BINARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->inject((IRBinaryArithmeticExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_BINARY_COMPARISON_EXPRESSION_NODE)) {
        return this->inject((IRBinaryComparisonExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_UNARY_ARITHMETIC_EXPRESSION_NODE)) {
        return this->inject((IRUnaryArithmeticExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_UNARY_NEGATE_EXPRESSION_NODE)) {
        return this->inject((IRUnaryNegateExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_LOGICAL_EXPRESSION_NODE)) {
        return this->inject((IRLogicalExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRTupleAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionInvocationExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionParameterInvocationExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRGlobalIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRClassPropertyAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRClassMethodInvocationExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    }
    throw std::logic_error("LiteralIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->getSource()->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                irExpression->getSource()->getType(),
                irExpression->getSource()->getValue(),
                { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() }
        );
        builder->get()->Insert(pointer);
        return builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    }

    auto sourceAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), sourceAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    builder->get()->Insert(pointer);
    return builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRBinaryArithmeticExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {

    auto irLeftNodeValue = irInjectorMap->getInjector(irExpression->getLeftNode()->getTypeSignature())->inject(
            irExpression->getLeftNode(), builder, irInjectorMap, irOperationType, irModule, scope);


    auto irRightNodeValue = irInjectorMap->getInjector(irExpression->getRightNode()->getTypeSignature())->inject(
            irExpression->getRightNode(), builder, irInjectorMap, irOperationType, irModule, scope);

    return builder->get()->CreateBinOp(irExpression->getValue()->getOpcode(), irLeftNodeValue, irRightNodeValue);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRBinaryComparisonExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {

    auto irLeftNodeValue = irInjectorMap->getInjector(irExpression->getLeftNode()->getTypeSignature())->inject(
            irExpression->getLeftNode(), builder, irInjectorMap, irOperationType, irModule, scope);

    auto irRightNodeValue = irInjectorMap->getInjector(irExpression->getRightNode()->getTypeSignature())->inject(
            irExpression->getRightNode(), builder, irInjectorMap, irOperationType, irModule, scope);
    return builder->get()->CreateCmp(irExpression->getValue()->getPredicate(), irLeftNodeValue, irRightNodeValue);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRUnaryArithmeticExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return builder->get()->Insert(irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRUnaryNegateExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return builder->get()->Insert(irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRLogicalExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {

    auto irLeftNodeValue = irInjectorMap->getInjector(irExpression->getLeftNode()->getTypeSignature())->inject(
            irExpression->getLeftNode(), builder, irInjectorMap, irOperationType, irModule, scope);

    auto irRightNodeValue = irInjectorMap->getInjector(irExpression->getRightNode()->getTypeSignature())->inject(
            irExpression->getRightNode(), builder, irInjectorMap, irOperationType, irModule, scope);

    return builder->get()->CreateBinOp(irExpression->getValue()->getOpcode(), irLeftNodeValue, irRightNodeValue);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjectorMap->getInjector(irExpression->getSourceExpression()->getTypeSignature())->inject(irExpression->getSourceExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    auto zeroIndex = builder->get()->getInt32(0);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto pointerToFirstElement = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceValue, { zeroIndex, pointerIndex });
    auto loadedPointerToFirstElement = builder->get()->CreateLoad(arrayPointerType->getPointerType(), pointerToFirstElement);
    auto indexValue = irInjectorMap->getInjector(irExpression->getIndexExpression()->getTypeSignature())->inject(irExpression->getIndexExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    auto pointerAtIndex = builder->get()->CreateInBoundsGEP(
            arrayPointerType->getPointerType(),
            loadedPointerToFirstElement,
            { indexValue }
    );
    return builder->get()->CreateLoad(
        irExpression->getIRType()->getSourceType()->getType(),
        pointerAtIndex
    );
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), sourceAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    builder->get()->Insert(pointer);
    return builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRFunctionInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, builder, irInjectorMap, irModule, scope);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRFunctionParameterInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, builder, irInjectorMap, irModule, scope);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRGlobalIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return builder->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return ClassPropertyAccessIRInjectorHelper::inject(irExpression, builder, irInjectorMap, irModule,
                                                       scope);
}

llvm::Value* LiteralIRInjectorStrategy::inject(IRClassMethodInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, builder, irInjectorMap, irModule, scope);
}