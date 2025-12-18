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
    IRType* _irFunctionType;
    std::vector<IRExpressionNode*> _arguments;
    IRType* _type;
    std::optional<IRInstructionNode*> _varArgsTypeValueArgument;
public:
    IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<IRInstructionNode*> varArgsTypeValueArgument = {});
    void markAsGlobal() override;
    bool isReferenced() override;
    std::optional<IRInstructionNode*> getVarArgsTypeValueArgument();
    std::vector<IRExpressionNode*>* getIRArguments();
    ASTFunctionInvocationExpressionNode* getNode();
    llvm::Value* getValue() override;
    IRType* getFunctionIRType();
    IRType* getIRType() override;
    FunctionInvocationTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
