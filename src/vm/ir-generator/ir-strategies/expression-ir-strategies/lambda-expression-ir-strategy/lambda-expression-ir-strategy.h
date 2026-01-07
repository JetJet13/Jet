//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H
#define JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-block-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-module-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-with-fat-arrow-expression-node.h"

class LambdaExpressionIRStrategy {
private:
    void setupParameters(LambdaExpressionTypeSignature* typeSignature, IRGenerator* irGenerator, IRLookupTable* scope, llvm::Function* irFunction, IRFunctionParameterListNode* functionParameterList, IRBlockNode* functionBlock, IRContext* irContext);
    llvm::Function* generateLambdaCleanupFunction(IRLambdaType* irLambdaType, IRGenerator* irGenerator, IRContext* irContext);
public:
    IRLambdaWithBlockExpressionNode* generate(ASTLambdaExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRLambdaWithFatArrowExpressionNode* generate(ASTLambdaWithFatArrowExpressionNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H
