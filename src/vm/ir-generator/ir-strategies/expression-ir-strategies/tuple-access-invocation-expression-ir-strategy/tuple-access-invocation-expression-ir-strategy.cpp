//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-invocation-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRExpressionNode> TupleAccessInvocationExpressionIRStrategy::generate(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<std::shared_ptr<IRFunctionArgumentNode>>();
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
    auto targetIndex = node->getObjectAccess()->getIndex()->getIndexValue();
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, irOperation);
    auto sourceType = sourceValue->getUnderlyingIRType();
    auto irStructRefType = std::dynamic_pointer_cast<IRStructRefType>(sourceType);
    auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irStructRefType->getStructIRType()->getIRTypeByIndex(targetIndex));

    auto callInstruction = llvm::CallInst::Create(irInvocableType->getIRFunctionType()->getType(), sourceValue->getValue(), argList);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return std::make_shared<IRTupleAccessInvocationExpressionNode>(node, sourceValue, callInstruction, irInvocableType, targetIndex, arguments, irReturnType);
}