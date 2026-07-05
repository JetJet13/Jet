//
// Created by Johny Georges on 2024-12-27.
//

#ifndef JETLANG_IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRClassMethodInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTClassMethodInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    llvm::Value* _irFunction;
    std::shared_ptr<IRType> _irFunctionType;
    std::vector<IRFunctionArgumentNode*> _arguments;
    std::shared_ptr<IRType> _type;
    IRInstructionNode* _classScopeArgument;
public:
    IRClassMethodInvocationExpressionNode(std::shared_ptr<ASTClassMethodInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, std::shared_ptr<IRType> type, IRInstructionNode* classScopeArgument);
    void markAsGlobal() override;
    IRInstructionNode* getClassScopeArgument();
    std::vector<IRFunctionArgumentNode*>* getIRArguments();
    llvm::CallInst* getValue() override;
    llvm::Value* getFunctionValue();
    std::shared_ptr<IRType> getFunctionIRType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE_H
