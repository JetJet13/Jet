//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../ir-type/ir-class-instance-type.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-ref-prototype-invocation-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRExpressionNode* ObjectAccessInvocationExpressionIRStrategy::generate(ASTObjectAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, new IROperation(IR_FUNCTION_ARGUMENT_OP)));
    }

    if (node->isArrayPrototypeInvocation()) {
        auto irArrayExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getArrayPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        return new IRArrayPrototypeInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, irArrayExpression);
    }

    if (node->isRefPrototypeInvocation()) {
        auto irRefExpression = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, new IROperation(IR_OPERAND_POINTER_OP));
        auto function = irContext->getModule()->getFunction(irGenerator->getRefPrototypeFunctionName(node->getName()));
        auto irFunctionType = irGenerator->generateFunctionIrType(function->getFunctionType());
        auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
        return new IRRefPrototypeInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, irRefExpression);
    }

    auto functionId = FunctionIdGenerator::generateFor(node);
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (sourceType->isClassInstanceType()) {
        auto classInstanceType = (IRClassInstanceType*)sourceType;
        auto irFunctionType = classInstanceType->getIRTypeForMethod(functionId).value();
        auto irFunction = IRInstructionNodeFactory::create(irContext->getModule()->getFunction(classInstanceType->getIRMethodName(functionId)), irGenerator->generateIrPointerType(irFunctionType));
        return new IRObjectAccessInvocationExpressionNode(node, irFunction, irFunctionType, arguments, irReturnType, sourceValue);
    } else if (sourceType->isStructRefType()) {
        auto irStructRefType = (IRStructRefType*)sourceType;
        auto targetIndex = irStructRefType->getStructIRType()->getIndexForKey(node->getName());
        auto irFunctionType = irStructRefType->getStructIRType()->getIRTypeForKey(node->getName());
        auto irStructAllocPointer = llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getType(), sourceValue->getValue(), { irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(irStructRefType->getStructIndex()) });
        auto loadedStructAlloc = new llvm::LoadInst(irStructRefType->getStructType(), irStructAllocPointer, "", false, irStructRefType->getAlignment());
        auto irFunction = IRInstructionNodeFactory::create(
                llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getStructIRType()->getType(), loadedStructAlloc, { irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(targetIndex) }),
                irGenerator->generateIrPointerType(irFunctionType),
                { irStructAllocPointer, loadedStructAlloc }
        );
        return new IRObjectAccessInvocationExpressionNode(node, irFunction, irFunctionType, arguments, irReturnType);
    } else {
        auto irStructType = (IRStructType*)sourceType;
        auto targetIndex = irStructType->getIndexForKey(node->getName());
        auto irFunctionType = irStructType->getIRTypeForKey(node->getName());
        auto irFunction = IRInstructionNodeFactory::create(
                llvm::GetElementPtrInst::CreateInBounds(irStructType->getType(), sourceValue->getValue(), { irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(targetIndex) }),
                irGenerator->generateIrPointerType()
        );
        return new IRObjectAccessInvocationExpressionNode(node, irFunction, irFunctionType, arguments, irReturnType);
    }
}