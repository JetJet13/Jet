//
// Created by Johny Georges on 2025-12-31.
//

#ifndef JETLANG_IR_LAMBDA_EXPRESSION_NODE_H
#define JETLANG_IR_LAMBDA_EXPRESSION_NODE_H

#include "../ir-expression-node.h"
#include "../../ir-function-nodes/ir-function-parameter-list-node.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-type/ir-lambda-type.h"

class IRLambdaExpressionNode : public IRExpressionNode {
public:
    virtual IRInstructionNode* getAllocation() = 0;
    virtual llvm::Function* getFunctionValue() = 0;
    virtual IRLambdaType* getIRType() = 0;
    virtual llvm::Function* getCleanupFunction() = 0;
    virtual IRLookupTable* getScope() = 0;
    virtual IRFunctionParameterListNode* getParameters() = 0;
    virtual IRBlockNode* getBlock() = 0;
};

#endif //JETLANG_IR_LAMBDA_EXPRESSION_NODE_H
