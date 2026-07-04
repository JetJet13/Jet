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
    IRFunctionParameterListNode* _irParameterList;
    IRBlockNode* _irBlock;
    IRLambdaType* _type;
    llvm::Function* _irCleanupFunction;
    IRInstructionNode* _irValue;
public:
    IRLambdaWithBlockExpressionNode(std::shared_ptr<ASTLambdaExpressionNode> node, IRInstructionNode* irValue, llvm::Function* irFunction, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type, llvm::Function* irCleanupFunction);
    IRInstructionNode* getAllocation() override;
    llvm::Function* getFunctionValue() override;
    llvm::Function* getCleanupFunction() override;
    IRFunctionParameterListNode* getParameters() override;
    IRBlockNode* getBlock() override;
    llvm::Value* getValue() override;
    IRLambdaType* getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE_H
