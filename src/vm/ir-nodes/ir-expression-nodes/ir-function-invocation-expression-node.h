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
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRFunctionInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTFunctionInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    IRInstructionNode* _irFunction;
    IRType* _irFunctionType;
    std::vector<IRFunctionArgumentNode*> _arguments;
    IRType* _type;
    std::optional<IRInstructionNode*> _varArgsTypeValueArgument;
public:
    IRFunctionInvocationExpressionNode(std::shared_ptr<ASTFunctionInvocationExpressionNode> node, IRInstructionNode* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, IRType* type, std::optional<IRInstructionNode*> varArgsTypeValueArgument = {});
    void markAsGlobal() override;
    std::optional<IRInstructionNode*> getVarArgsTypeValueArgument();
    std::vector<IRFunctionArgumentNode*>* getIRArguments();
    std::shared_ptr<ASTFunctionInvocationExpressionNode> getNode();
    llvm::CallInst* getValue() override;
    IRInstructionNode* getFunction();
    llvm::Value* getFunctionValue();
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
