//
// Created by Johny Georges on 2024-11-08.
//

#ifndef JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"

class IRFunctionInvocationExpressionNode : public IRExpressionNode {
private:
    ASTFunctionInvocationExpressionNode* _node;
    llvm::Value* _irFunction;
    IRFunctionType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
    std::optional<IRInstructionNode*> _lambdaScopeArgument;
public:
    IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::Value* irFunction, IRFunctionType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<IRInstructionNode*> lambdaScopeArgument = {});
    std::optional<IRInstructionNode*> getLambdaScopeArgument();
    std::vector<IRExpressionNode*>* getIRArguments();
    llvm::Value* getValue() override;
    IRFunctionType* getFunctionIRType();
    IRType* getIRType() override;
    FunctionInvocationTypeSignature* getTypeSignature() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
