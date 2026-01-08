//
// Created by Johny Georges on 2025-06-09.
//

#include "concat-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRConcatExpressionNode* ConcatExpressionIRStrategy::generate(ASTConcatExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, irOperation);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, irOperation);
    auto irType = (IRArrayPointerType*)irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto function = node->getTypeSignature()->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)
            ? irContext->getIRModule()->getStringConcatFunction()
            : irContext->getIRModule()->getArrayConcatFunction();
    auto concatCall = llvm::CallInst::Create(
            function,
            irGenerator->generateArgumentPlaceholderList(irGenerator->generateFunctionIrType(function->getFunctionType()))
    );
    return new IRConcatExpressionNode(
            node,
            concatCall,
            leftExpressionIr,
            rightExpressionIr,
            irType
    );
}