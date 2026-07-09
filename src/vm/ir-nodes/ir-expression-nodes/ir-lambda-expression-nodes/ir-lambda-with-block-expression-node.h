//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE_H
#define JETLANG_IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE_H

#include <llvm/IR/Function.h>
#include "../../ir-block-nodes/ir-block-node.h"
#include "../../ir-function-nodes/ir-function-parameter-list-node.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../ir-type/ir-lambda-type.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "ir-lambda-expression-node.h"

class IRLambdaWithBlockExpressionNode : public IRLambdaExpressionNode {
private:
    std::shared_ptr<ASTLambdaExpressionNode> _node;
    llvm::Function* _irFunction;
    std::shared_ptr<IRFunctionParameterListNode> _irParameterList;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRLambdaType> _type;
    llvm::Function* _irCleanupFunction;
    std::shared_ptr<IRInstructionNode> _irValue;
public:
    IRLambdaWithBlockExpressionNode(std::shared_ptr<ASTLambdaExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, llvm::Function* irFunction, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRLambdaType> type, llvm::Function* irCleanupFunction);
    std::shared_ptr<IRInstructionNode> getAllocation() override;
    llvm::Function* getFunctionValue() override;
    llvm::Function* getCleanupFunction() override;
    std::shared_ptr<IRFunctionParameterListNode> getParameters() override;
    std::shared_ptr<IRBlockNode> getBlock() override;
    llvm::Value* getValue() override;
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE_H
