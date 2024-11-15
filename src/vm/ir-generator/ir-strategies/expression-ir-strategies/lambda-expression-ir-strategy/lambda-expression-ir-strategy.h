//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H
#define JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../ir-nodes/ir-module-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-with-fat-arrow-expression-node.h"

class LambdaExpressionIRStrategy {
public:
    IRLambdaExpressionNode* generate(ASTLambdaExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
    IRLambdaWithFatArrowExpressionNode* generate(ASTLambdaWithFatArrowExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_LAMBDA_EXPRESSION_IR_STRATEGY_H
