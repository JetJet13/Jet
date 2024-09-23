//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"
#include "../../../ir-util-functions/array-access-ir-function/array-access-ir-function.h"

IRArrayAccessExpressionNode* ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto arrayAccessFunction = irModule->getModule()->getFunction(ArrayAccessIRFunction::getArrayAccessIRFunctionName());
    if (irModule->getModule()->getFunction(ArrayAccessIRFunction::getArrayAccessIRFunctionName()) == nullptr) {
        ArrayAccessIRFunction::generateArrayAccessFunction(irGenerator, context, irModule);
        arrayAccessFunction = irModule->getModule()->getFunction(ArrayAccessIRFunction::getArrayAccessIRFunctionName());
    }

    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irModule, IR_OPERAND_OP);
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope, irModule, IR_OPERAND_OP);
    sourceValue->getIRType()->print();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    return new IRArrayAccessExpressionNode(node, sourceValue, indexValue, irType, arrayAccessFunction);
}