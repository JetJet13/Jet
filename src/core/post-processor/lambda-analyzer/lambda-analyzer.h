//
// Created by Johny Georges on 2025-11-15.
//

#ifndef JETLANG_LAMBDA_ANALYZER_H
#define JETLANG_LAMBDA_ANALYZER_H

#include "../../ast/ast-nodes/ast-node.h"
#include "../../ast-lookup-table/ast-lookup-table.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"
#include "../../ast-traverser/ast-traverser.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"

class LambdaAnalyzer {
private:
    ASTTraverser _astTraverser;
    void analyzeLambdaReturnExpression(ASTLambdaReturnExpressionNode* lambdaReturnExpressionNode, ASTLookupTable* scope);
    void analyzeLambdaExpression(ASTLambdaExpressionNode* lambdaExpressionNode, ASTLookupTable* scope);
public:
    LambdaAnalyzer();
    void analyze(ASTNode* nodeToAnalyze, ASTLookupTable* rootScope);
};

#endif //JETLANG_LAMBDA_ANALYZER_H
