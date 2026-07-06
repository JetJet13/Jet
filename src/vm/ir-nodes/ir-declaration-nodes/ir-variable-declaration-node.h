//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_VARIABLE_DECLARATION_NODE_H
#define JETLANG_IR_VARIABLE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-declaration-node.h"
#include "../ir-instruction-node.h"

class IRVariableDeclarationNode : public IRDeclarationNode {
private:
    std::shared_ptr<ASTVariableDeclarationNode> _node;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::optional<std::shared_ptr<IRInstructionNode>> _irGlobalVariable;
    std::optional<std::shared_ptr<IRInstructionNode>> _irArc;
    llvm::Value* _variableNameIRValue;
public:
    IRVariableDeclarationNode(std::shared_ptr<ASTVariableDeclarationNode> astNode, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRExpressionNode> irExpression, llvm::Value* variableNameIRValue, std::optional<std::shared_ptr<IRInstructionNode>> irGlobalVariable = {}, std::optional<std::shared_ptr<IRInstructionNode>> irArc = {});
    std::string getVariableName();
    llvm::Value* getVariableNameIRValue();
    llvm::Value* getValue() override;
    llvm::Type* getAllocatedType();
    std::shared_ptr<IRType> getAllocatedIRType();
    std::shared_ptr<IRInstructionNode> getIRValue();
    std::shared_ptr<IRExpressionNode> getIRExpression();
    bool toBeFreedDirectly();
    bool isLambdaVariable();
    std::optional<std::shared_ptr<IRInstructionNode>> getGlobalVariable();
    std::optional<std::shared_ptr<IRInstructionNode>> getArc();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_VARIABLE_DECLARATION_NODE_H
