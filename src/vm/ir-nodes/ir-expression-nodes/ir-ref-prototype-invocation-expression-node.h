//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRRefPrototypeInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    llvm::Value* _irFunction;
    std::shared_ptr<IRType> _irFunctionType;
    std::vector<std::shared_ptr<IRFunctionArgumentNode>> _arguments;
    std::shared_ptr<IRType> _type;
    std::shared_ptr<IRExpressionNode> _irRef;
public:
    IRRefPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::shared_ptr<IRExpressionNode> irRef);
    void markAsGlobal() override;
    std::shared_ptr<IRExpressionNode> getIRRefValue();
    std::vector<std::shared_ptr<IRFunctionArgumentNode>>* getIRArguments();
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

#endif //JETLANG_IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE_H
