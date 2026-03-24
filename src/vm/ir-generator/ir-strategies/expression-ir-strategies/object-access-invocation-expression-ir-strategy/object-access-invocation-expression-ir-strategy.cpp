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
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-method-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-prototype-invocation-expression-node.h"

IRExpressionNode* ObjectAccessInvocationExpressionIRStrategy::generate(ASTObjectAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRFunctionArgumentNode*>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
            irGenerator->generateFor(
                    argument,
                    i,
                    scope,
                    irContext,
                    new IROperation(IR_FUNCTION_ARGUMENT_OP),
                    node->getInvocableTypeSignature()
            )
        );
    }
    auto argList = irGenerator->generateArgumentPlaceholderListForFunction(node->getInvocableTypeSignature(), &arguments, scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto functionId = node->getName();
    if (node->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classTypeSignature = (ClassTypeSignature*)node->getSource()->getSource()->getTypeSignature();
        auto irClassType = (IRClassType*)scope->findGlobalType(classTypeSignature->getId()).value();
        auto functionName = irClassType->getIRMethodName(functionId);
        auto irFunctionType = irClassType->getIRTypeForStaticMethod(functionName).value();
        auto irFunction = IRInstructionNodeFactory::create(irContext->getModule()->getFunction(irClassType->getIRMethodName(functionId)), irGenerator->generateIrPointerType(irFunctionType));
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), irFunction->getValue(), argList);
        return new IRClassStaticMethodInvocationExpressionNode(node, irFunction, callInstruction, irFunctionType, arguments, irReturnType);
    }

    if (node->isRefPrototypeInvocation() && irGenerator->getRefPrototypeFunctionName(node->getName())) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getRefPrototypeFunctionName(node->getName()).value());
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto refPrototypeArgList = std::vector<llvm::Value*>();
        refPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        for (int i = 0; i < arguments.size(); ++i) {
            refPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        }

        if (function->getFunctionType()->getNumParams() > refPrototypeArgList.size()) {
            refPrototypeArgList.push_back(irGenerator->generatePlaceholderTypeValueArgument());
        }
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, refPrototypeArgList);
        return new IRRefPrototypeInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    if (node->isArrayPrototypeInvocation()) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
        auto function = irContext->getModule()->getFunction(irGenerator->getArrayPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto arrayPrototypeArgList = std::vector<llvm::Value*>();
        arrayPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        for (int i = 0; i < arguments.size(); ++i) {
            arrayPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        }

        if (function->getFunctionType()->getNumParams() > arrayPrototypeArgList.size()) {
            arrayPrototypeArgList.push_back(irGenerator->generatePlaceholderTypeValueArgument());
        }

        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, arrayPrototypeArgList);
        return new IRArrayPrototypeInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    if (node->isStringPrototypeInvocation()) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
        auto function = irContext->getModule()->getFunction(irGenerator->getStringPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto stringPrototypeArgList = std::vector<llvm::Value*>();
        stringPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        for (int i = 0; i < arguments.size(); ++i) {
            stringPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        }

        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, stringPrototypeArgList);
        return new IRStringPrototypeInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    if (sourceType->isClassInstanceType()) {
        auto classInstanceType = (IRClassInstanceType*)sourceType;
        auto irFunctionType = classInstanceType->getIRTypeForMethod(functionId).value();
        auto irFunction = IRInstructionNodeFactory::create(irContext->getModule()->getFunction(classInstanceType->getIRMethodName(functionId)), irGenerator->generateIrPointerType(irFunctionType));
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), irFunction->getValue(), argList);
        return new IRObjectAccessInvocationExpressionNode(node, irFunction, callInstruction, irFunctionType, arguments, irReturnType, sourceValue);
    }


    auto irStructRefType = (IRStructRefType*)sourceType;
    auto targetIndex = irStructRefType->getStructIRType()->getIndexForKey(node->getName());
    auto irInvocableType = (IRInvocableType*)irStructRefType->getStructIRType()->getIRTypeForKey(node->getName());
    auto irStructAllocPointer = llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getType(), sourceValue->getValue(), { irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(irStructRefType->getStructIndex()) });
    auto loadedStructAlloc = irGenerator->generateLoadInstruction(irStructAllocPointer, irGenerator->generateIrPointerType());
    auto pointerToValue = llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getStructIRType()->getType(), loadedStructAlloc, { irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(targetIndex) });
    auto irFunction = IRInstructionNodeFactory::create(
            irGenerator->generateLoadInstruction(pointerToValue, irInvocableType),
            irGenerator->generateIrPointerType(irInvocableType),
            { irStructAllocPointer, loadedStructAlloc, pointerToValue }
    );
    auto callInstruction = llvm::CallInst::Create(irInvocableType->getIRFunctionType()->getType(), irFunction->getValue(), argList);
    return new IRObjectAccessInvocationExpressionNode(node, irFunction, callInstruction, irInvocableType, arguments, irReturnType);
}
