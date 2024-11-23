//
// Created by Johny Georges on 2024-11-08.
//

#ifndef JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"

class IRFunctionInvocationExpressionNode : public IRExpressionNode {
private:
    ASTFunctionInvocationExpressionNode* _node;
    llvm::Function* _irFunction;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
    std::optional<llvm::Value*> _lambdaScopeArgument;
public:
    IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::Function* irFunction, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<llvm::Value*> lambdaScopeArgument = {});
    std::optional<llvm::Value*> getLambdaScopeArgument();
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Function* getValue() override;
    IRType* getIRType() override;
    FunctionInvocationTypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
