//
// Created by Johny Georges on 2024-11-14.
//

#ifndef JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
#define JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H

#include <llvm/IR/Function.h>
#include "../../ir-block-nodes/ir-block-node.h"
#include "../../ir-function-nodes/ir-function-parameter-list-node.h"
#include "../../../ir-type/ir-lambda-type.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "ir-lambda-expression-node.h"

class IRLambdaWithFatArrowExpressionNode : public IRLambdaExpressionNode {
private:
    std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> _node;
    llvm::Function* _irFunction;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::shared_ptr<IRFunctionParameterListNode> _irParameterList;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRLambdaType> _type;
    llvm::Function* _irCleanupFunction;
    std::shared_ptr<IRExpressionNode> _irReturnExpression;
public:
    IRLambdaWithFatArrowExpressionNode(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, llvm::Function* irFunction, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRLambdaType> type, llvm::Function* irCleanupFunction, std::shared_ptr<IRExpressionNode> irReturnExpression);
    std::shared_ptr<IRExpressionNode> getReturnExpression();
    std::shared_ptr<IRInstructionNode> getAllocation() override;
    llvm::Function* getFunctionValue() override;
    llvm::Function* getCleanupFunction() override;
    std::shared_ptr<IRBlockNode> getBlock() override;
    std::shared_ptr<IRFunctionParameterListNode> getParameters() override;
    llvm::Value* getValue() override;
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE_H
