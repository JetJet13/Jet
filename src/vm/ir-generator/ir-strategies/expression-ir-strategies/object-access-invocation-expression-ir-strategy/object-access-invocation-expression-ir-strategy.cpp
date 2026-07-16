//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-shared-ptr-prototype-invocation-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-method-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-prototype-invocation-expression-node.h"

std::shared_ptr<IRExpressionNode> ObjectAccessInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto arguments = std::vector<std::shared_ptr<IRFunctionArgumentNode>>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
            irGenerator->generateFor(
                    argument,
                    i,
                    scope,
                    irContext,
                    std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP),
                    node->getInvocableTypeSignature()
            )
        );
    }
    auto argList = irGenerator->generateArgumentPlaceholderListForFunction(node->getInvocableTypeSignature(), &arguments, scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);


    if (node->isSharedPtrPrototypeInvocation() && irGenerator->getSharedPtrPrototypeFunctionName(node->getName())) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getSharedPtrPrototypeFunctionName(node->getName()).value());
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto sharedPtrPrototypeArgList = std::vector<llvm::Value*>();
        sharedPtrPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        for (int i = 0; i < arguments.size(); ++i) {
            sharedPtrPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        }

        if (function->getFunctionType()->getNumParams() > sharedPtrPrototypeArgList.size()) {
            sharedPtrPrototypeArgList.push_back(irGenerator->generatePlaceholderTypeValueArgument());
        }
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, sharedPtrPrototypeArgList);
        return std::make_shared<IRSharedPtrPrototypeInvocationExpressionNode>(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    if (node->isArrayPrototypeInvocation()) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying());
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
        return std::make_shared<IRArrayPrototypeInvocationExpressionNode>(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    if (node->isStringPrototypeInvocation()) {
        auto irExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying());
        auto function = irContext->getModule()->getFunction(irGenerator->getStringPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto stringPrototypeArgList = std::vector<llvm::Value*>();
        stringPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        for (int i = 0; i < arguments.size(); ++i) {
            stringPrototypeArgList.push_back(irGenerator->generateConstantPointer());
        }

        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, stringPrototypeArgList);
        return std::make_shared<IRStringPrototypeInvocationExpressionNode>(node, function, callInstruction, irFunctionType, arguments, irReturnType, irExpression);
    }

    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    if (sourceType->isClassInstanceType()) {
        auto classInstanceType = std::dynamic_pointer_cast<IRClassInstanceType>(sourceType);
        auto irFunctionType = classInstanceType->getIRTypeForMethod(node->getName()).value();
        auto irFunction = irContext->getModule()->getFunction(classInstanceType->getIRMethodName(node->getName()));
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), irFunction, argList);
        return std::make_shared<IRObjectAccessInvocationExpressionNode>(node, sourceValue, callInstruction, irFunctionType, 0, arguments, irReturnType, sourceValue);
    }

    if (sourceType->isClassType()) {
        auto irClassType = std::dynamic_pointer_cast<IRClassType>(sourceType);
        auto functionName = irClassType->getIRMethodName(node->getName());
        auto irFunctionType = irClassType->getIRTypeForStaticMethod(functionName).value();
        auto irFunction = IRInstructionNodeFactory::create(irContext->getModule()->getFunction(irClassType->getIRMethodName(node->getName())), irGenerator->generateIrPointerType(irFunctionType));
        auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), irFunction->getValue(), argList);
        return std::make_shared<IRClassStaticMethodInvocationExpressionNode>(node, irFunction, callInstruction, irFunctionType, arguments, irReturnType);
    }

    auto irStructRefType = std::dynamic_pointer_cast<IRStructRefType>(sourceType);
    auto targetIndex = irStructRefType->getStructIRType()->getIndexForKey(node->getName());
    auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irStructRefType->getStructIRType()->getIRTypeForKey(node->getName()));
    auto callInstruction = llvm::CallInst::Create(irInvocableType->getIRFunctionType()->getType(), sourceValue->getValue(), argList);
    return std::make_shared<IRObjectAccessInvocationExpressionNode>(node, sourceValue, callInstruction, irInvocableType, targetIndex, arguments, irReturnType);
}
