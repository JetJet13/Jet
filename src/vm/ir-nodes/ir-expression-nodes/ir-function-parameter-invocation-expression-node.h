//
// Created by Johny Georges on 2024-11-28.
//

#ifndef JETLANG_IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../../ir-type/ir-function-parameter-type.h"

class IRFunctionParameterInvocationExpressionNode : public IRExpressionNode {
private:
    ASTFunctionInvocationExpressionNode* _node;
    llvm::Value* _irFunction;
    llvm::Value* _irFunctionScopeArgument;
    IRFunctionParameterType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
public:
    IRFunctionParameterInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::Value* irFunction, llvm::Value* irFunctionScopeArgument, IRFunctionParameterType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type);
    void markAsGlobal() override;
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Value* getValue() override;
    llvm::Value* getFunction();
    llvm::Value* getFunctionScopeArgument();
    IRFunctionParameterType* getFunctionIRType();
    IRType* getIRType() override;
    FunctionInvocationTypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE_H
