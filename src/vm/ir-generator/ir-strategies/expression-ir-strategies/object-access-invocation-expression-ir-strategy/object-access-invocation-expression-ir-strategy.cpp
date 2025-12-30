//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-ref-prototype-invocation-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-type/ir-class-instance-type.h"

IRExpressionNode* ObjectAccessInvocationExpressionIRStrategy::generate(ASTObjectAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, new IROperation(IR_FUNCTION_ARGUMENT_OP)));
    }

    if (node->isArrayPrototypeInvocation()) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getArrayPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType);
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
        return new IRArrayPrototypeInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    if (node->isRefPrototypeInvocation()) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getRefPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType);
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
        return new IRRefPrototypeInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    auto functionId = FunctionIdGenerator::generateFor(node);
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (sourceType->isClassInstanceType()) {
        auto classInstanceType = (IRClassInstanceType*)sourceType;
        auto irFunctionType = classInstanceType->getIRTypeForMethod(functionId).value();
        auto irFunction = IRInstructionNodeFactory::create(irContext->getModule()->getFunction(classInstanceType->getIRMethodName(functionId)), irGenerator->generateIrPointerType(irFunctionType));
        auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType);
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), irFunction->getValue(), argList);
        return new IRObjectAccessInvocationExpressionNode(node, irFunction, callInstruction, irFunctionType, arguments, irReturnType, sourceValue);
    }

    auto irStructRefType = (IRStructRefType*)sourceType;
    auto targetIndex = irStructRefType->getStructIRType()->getIndexForKey(node->getName());
    auto irFunctionParameterType = (IRFunctionParameterType*)irStructRefType->getStructIRType()->getIRTypeForKey(node->getName());
    auto irStructAllocPointer = llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getType(), sourceValue->getValue(), { irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(irStructRefType->getStructIndex()) });
    auto loadedStructAlloc = irGenerator->generateLoadInstruction(irStructAllocPointer, irGenerator->generateIrPointerType());
    auto pointerToValue = llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getStructIRType()->getType(), loadedStructAlloc, { irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(targetIndex) });
    auto irFunction = IRInstructionNodeFactory::create(
            irGenerator->generateLoadInstruction(pointerToValue, irFunctionParameterType),
            irGenerator->generateIrPointerType(irFunctionParameterType),
            { irStructAllocPointer, loadedStructAlloc, pointerToValue }
    );
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionParameterType);
    auto callInstruction = llvm::CallInst::Create(irFunctionParameterType->getIRFunctionType()->getType(), irFunction->getValue(), argList);
    return new IRObjectAccessInvocationExpressionNode(node, irFunction, callInstruction, irFunctionParameterType, arguments, irReturnType);
}
