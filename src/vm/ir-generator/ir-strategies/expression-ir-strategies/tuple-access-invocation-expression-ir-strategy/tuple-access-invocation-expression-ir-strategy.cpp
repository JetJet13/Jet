//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-invocation-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRExpressionNode* TupleAccessInvocationExpressionIRStrategy::generate(ASTTupleAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
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
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = sourceValue->getUnderlyingIRType();
    auto irStructRefType = (IRStructRefType*)sourceType;
    auto targetIndex = node->getObjectAccess()->getIndex()->getIndexValue();
    auto irInvocableType = (IRInvocableType*)irStructRefType->getStructIRType()->getIRTypeByIndex(targetIndex);
    auto irTupleAllocPointer = llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getType(), sourceValue->getValue(), {irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(irStructRefType->getStructIndex()) });
    auto loadedTupleAlloc = irGenerator->generateLoadInstruction(irTupleAllocPointer, irGenerator->generateIrPointerType());
    auto pointerToValue = llvm::GetElementPtrInst::CreateInBounds(irStructRefType->getStructIRType()->getType(), loadedTupleAlloc, {irGenerator->generateIntConstant(0), irGenerator->generateIntConstant(targetIndex) });
    auto irFunction = IRInstructionNodeFactory::create(
            irGenerator->generateLoadInstruction(pointerToValue, irInvocableType),
            irGenerator->generateIrPointerType(irInvocableType),
            { irTupleAllocPointer, loadedTupleAlloc, pointerToValue }
    );
    auto callInstruction = llvm::CallInst::Create(irInvocableType->getIRFunctionType()->getType(), irFunction->getValue(), argList);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRTupleAccessInvocationExpressionNode(node, irFunction, callInstruction, irInvocableType, arguments, irReturnType);
}