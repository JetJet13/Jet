// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_BLOCK_NODE_H
#define JETLANG_IR_BLOCK_NODE_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "../ir-node.h"
#include "../ir-declaration-nodes/ir-variable-declaration-node.h"
#include "../ir-statement-nodes/ir-function-return-expression-node.h"
#include "../../types/ir-block-type.h"
#include "../ir-function-nodes/ir-function-parameter-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../ir-node-to-free.h"

class IRBlockNode : public std::enable_shared_from_this<IRBlockNode> {
protected:
    llvm::BasicBlock* _irValue;
    IRBlockType _type;
    std::shared_ptr<IRLookupTable> _scope;
    std::unique_ptr<llvm::IRBuilder<>> _builder;
    std::vector<std::shared_ptr<IRNode>> _body;
    std::vector<std::shared_ptr<IRBlockNode>> _childBlocks;
    std::vector<std::shared_ptr<IRBlockNode>> _nestedBlocks;
    std::vector<std::shared_ptr<IRBlockNode>> _successors;
    std::optional<std::shared_ptr<IRBlockNode>> _parentBlock;
    std::optional<std::shared_ptr<IRBlockNode>> _nestedParentBlock;
    std::vector<std::shared_ptr<IRNodeToFree>> _nodesToFree;
    std::optional<std::shared_ptr<IRFunctionReturnExpressionNode>> _returnExpression;
    bool _allowedToFreeNodes = true;
    bool _representsRealBlock = true;
public:
    IRBlockNode(llvm::BasicBlock* irValue, IRBlockType type, std::shared_ptr<IRLookupTable> scope);
    bool hasReturnStatement();
    bool hasBranchInstruction();
    bool hasReturnInstruction();
    bool isReachable();
    bool isUnreachable();
    bool isAllowedToFreeNodes();
    bool isRealBlock();
    void preventFreeingNodes();
    std::shared_ptr<IRBlockNode> markAsFakeBlock();
    std::shared_ptr<IRLookupTable> getScope();
    llvm::BasicBlock* getBlock();
    std::vector<std::shared_ptr<IRNode>>* getBody();
    void insert(std::shared_ptr<IRNode> irNode);
    std::unique_ptr<llvm::IRBuilder<>>* getBuilder();
    void addVoidReturn();
    bool hasNodesToFree();
    void addExpressionToFree(std::shared_ptr<IRExpressionNode> expressionNode, std::optional<std::shared_ptr<IRBlockNode>> associatedIRBlock = {});
    void addVariableToFree(std::shared_ptr<IRVariableDeclarationNode> variableNode, std::optional<std::shared_ptr<IRBlockNode>> associatedIRBlock = {});
    void addLambdaVariableToFree(std::shared_ptr<IRVariableDeclarationNode> variableNode, std::optional<std::shared_ptr<IRBlockNode>> associatedIRBlock = {});
    std::vector<std::shared_ptr<IRNodeToFree>>* getNodesToFree();
    std::vector<std::shared_ptr<IRNodeToFree>> getNestedParentsNodesToFree();
    void setFinalBlockForNodesToFree(std::shared_ptr<IRBlockNode> irBlock);
    virtual void setInsertionPointBeforeLastInstruction();
    virtual void setInsertionPointBeforeFirstInstruction();
    virtual void resetInsertionPoint();
    virtual void removeLastInstruction();
    void adoptNodesToFreeFrom(std::shared_ptr<IRBlockNode> other);
    void addReturnExpression(std::shared_ptr<IRFunctionReturnExpressionNode> returnExpressionNode);
    std::optional<std::shared_ptr<IRFunctionReturnExpressionNode>> getReturnExpression();
    void createChild();
    std::vector<std::shared_ptr<IRBlockNode>>* getSuccessors();
    std::shared_ptr<std::set<std::shared_ptr<IRBlockNode>>> getAllSuccessors();
    std::set<std::shared_ptr<IRBlockNode>> getAllChildrenThatReturn();
    std::vector<std::shared_ptr<IRBlockNode>>* getNestedBlocks();
    bool hasNestedBlocks();
    bool shouldFreeNodes();
    bool needsToFreeItsNodes();
    bool allImmediateNestedBlocksReturn();
    void nest(std::shared_ptr<IRBlockNode> irBlock);
    std::shared_ptr<IRBlockNode> getLastChildOrSelf();
    std::optional<std::shared_ptr<IRBlockNode>> getParentBlock();
    std::optional<std::shared_ptr<IRBlockNode>> getNestedParentBlock();
    bool is(IRBlockType blockType);
    bool isOneOf(std::vector<IRBlockType> blockTypes);
    bool canReturn();
    bool isEntryBlock();
    void setParentBlock(std::shared_ptr<IRBlockNode> parentIRBlock);
    void setNestedParentBlock(std::shared_ptr<IRBlockNode> nestedParentIRBlock);
};

#endif //JETLANG_IR_BLOCK_NODE_H
