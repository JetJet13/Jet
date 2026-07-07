//
// Created by Johny Georges on 2025-06-09.
//

#include "concat-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRConcatExpressionNode> ConcatExpressionIRStrategy::generate(std::shared_ptr<ASTConcatExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::shared_ptr<IROperation> irOperation) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, irOperation);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, irOperation);
    auto irType = std::dynamic_pointer_cast<IRArrayPointerType>(irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext));
    auto function = node->getTypeSignature()->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)
            ? irContext->getIRModule()->getStringConcatFunction()
            : irContext->getIRModule()->getArrayConcatFunction();
    auto args = std::vector({ leftExpressionIr, rightExpressionIr });
    auto placeholderArgs = node->getTypeSignature()->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)
            ? std::vector<llvm::Value*>({
                irGenerator->generateConstantPointer(),
                irGenerator->generateConstantPointer()
              })
            : std::vector<llvm::Value*>({
                irGenerator->generateConstantPointer(),
                irGenerator->generateConstantPointer(),
                irGenerator->generatePlaceholderTypeValueArgument()
              });
    auto concatCall = llvm::CallInst::Create(
            function,
            placeholderArgs
    );
    return std::make_shared<IRConcatExpressionNode>(
            node,
            concatCall,
            leftExpressionIr,
            rightExpressionIr,
            irType
    );
}