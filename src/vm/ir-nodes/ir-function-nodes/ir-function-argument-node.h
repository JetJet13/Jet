//
// Created by Johny Georges on 2026-02-09.
//

#ifndef JETLANG_IR_FUNCTION_ARGUMENT_NODE_H
#define JETLANG_IR_FUNCTION_ARGUMENT_NODE_H

#include <llvm/IR/Argument.h>
#include "../ir-node.h"
#include "../../ir-type/ir-parameter-type.h"
#include "../../../core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../ir-expression-nodes/ir-expression-node.h"
#include "../../ir-operation/ir-operation.h"

class IRFunctionArgumentNode : public IRNode {
private:
    IRExpressionNode* _irArgument;
    IROperation* _irOperation;
    std::optional<ParameterListItemTypeSignature*> _parameterTypeSignature;
    void initIROperation();
public:
    IRFunctionArgumentNode(IRExpressionNode* irArgument);
    IRFunctionArgumentNode(IRExpressionNode* irArgument, IROperation* irOperation);
    IRFunctionArgumentNode(IRExpressionNode* irArgument, ParameterListItemTypeSignature* parameterTypeSignature);
    IRExpressionNode* getArgument();
    IROperation* getOperation();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_ARGUMENT_NODE_H
