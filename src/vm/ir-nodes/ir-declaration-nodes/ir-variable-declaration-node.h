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
    IRInstructionNode* _irValue;
    IRExpressionNode* _irExpression;
    std::optional<IRInstructionNode*> _irGlobalVariable;
    std::optional<IRInstructionNode*> _irArc;
    llvm::Value* _variableNameIRValue;
public:
    IRVariableDeclarationNode(std::shared_ptr<ASTVariableDeclarationNode> astNode, IRInstructionNode* irValue, IRExpressionNode* irExpression, llvm::Value* variableNameIRValue, std::optional<IRInstructionNode*> irGlobalVariable = {}, std::optional<IRInstructionNode*> irArc = {});
    std::string getVariableName();
    llvm::Value* getVariableNameIRValue();
    llvm::Value* getValue() override;
    llvm::Type* getAllocatedType();
    IRType* getAllocatedIRType();
    IRInstructionNode* getIRValue();
    IRExpressionNode* getIRExpression();
    bool toBeFreedDirectly();
    bool isLambdaVariable();
    std::optional<IRInstructionNode*> getGlobalVariable();
    std::optional<IRInstructionNode*> getArc();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_VARIABLE_DECLARATION_NODE_H
