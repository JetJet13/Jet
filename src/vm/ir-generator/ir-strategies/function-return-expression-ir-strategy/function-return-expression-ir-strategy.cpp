//
// Created by Johny Georges on 2024-07-13.
//

#include "function-return-expression-ir-strategy.h"

IRFunctionReturnExpressionNode* FunctionReturnExpressionIRStrategy::generate(ASTFunctionReturnExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpression(), scope, irModule);
    return new IRFunctionReturnExpressionNode(node, irExpressionNode);
}