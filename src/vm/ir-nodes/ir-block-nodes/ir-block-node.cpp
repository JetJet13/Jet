//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"
#include "../../../shared/utils/logger/logger.h"

IRBlockNode::IRBlockNode(llvm::BasicBlock* irValue, IRBlockType type) {
    _irValue = irValue;
    _type = type;
    _builder = std::make_unique<llvm::IRBuilder<>>(_irValue);
}

bool IRBlockNode::hasReturnStatement() {
    if (_body.empty()) {
        return false;
    }
    return _body.back()->is(IR_FUNCTION_RETURN_EXPRESSION_NODE);
}

bool IRBlockNode::hasBranchInstruction() {
    if (_irValue->getTerminator()) {
        return llvm::isa<llvm::BranchInst>(_irValue->getTerminator());
    }
    return false;
}

llvm::BasicBlock* IRBlockNode::getBlock() {
    return _irValue;
}

std::vector<IRNode*>* IRBlockNode::getBody() {
    return &_body;
}

void IRBlockNode::insert(IRNode* irNode) {
    _body.push_back(irNode);
}

std::unique_ptr<llvm::IRBuilder<>>* IRBlockNode::getBuilder() {
    return &_builder;
}

void IRBlockNode::addVoidReturn() {
    _builder.get()->CreateRetVoid();
}

bool IRBlockNode::hasVariablesToFree() {
    return this->getVariablesToFree()->size() > 0;
}

void IRBlockNode::addReturnExpression(IRFunctionReturnExpressionNode* returnExpressionNode) {
    _returnExpression = returnExpressionNode;
}

void IRBlockNode::addExpressionToFree(IRExpressionNode* expressionNode) {
    _expressionsToFree.insert(_expressionsToFree.begin(), expressionNode);
}

void IRBlockNode::addVariableToFree(IRVariableDeclarationNode* variableNode) {
    _variablesToFree.insert(_variablesToFree.begin(), variableNode);
}

void IRBlockNode::addLambdaVariableToFree(IRVariableDeclarationNode* variableNode) {
    _lambdaVariablesToFree.insert(_lambdaVariablesToFree.begin(), variableNode);
}

std::vector<IRExpressionNode*>* IRBlockNode::getExpressionsToFree() {
    auto allExpressionsToFree = new std::vector<IRExpressionNode*>();
    allExpressionsToFree->insert(allExpressionsToFree->begin(), _expressionsToFree.begin(), _expressionsToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->is(IR_BASIC_BT)) {
            auto moreExpressionsToFree = successorBlock->getExpressionsToFree();
            allExpressionsToFree->insert(
                    allExpressionsToFree->begin(),
                    moreExpressionsToFree->begin(),
                    moreExpressionsToFree->end()
            );

        }
    }
    return allExpressionsToFree;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getVariablesToFree() {
    auto allVariablesToFree = new std::vector<IRVariableDeclarationNode*>();
    allVariablesToFree->insert(allVariablesToFree->begin(), _variablesToFree.begin(), _variablesToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->is(IR_BASIC_BT)) {
            auto moreVariablesToFree = successorBlock->getVariablesToFree();
            allVariablesToFree->insert(
                    allVariablesToFree->begin(),
                    moreVariablesToFree->begin(),
                    moreVariablesToFree->end()
            );

        }
    }
    return allVariablesToFree;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getLambdaVariablesToFree() {
    auto allLambdaVariablesToFree = new std::vector<IRVariableDeclarationNode*>();
    allLambdaVariablesToFree->insert(allLambdaVariablesToFree->begin(), _lambdaVariablesToFree.begin(), _lambdaVariablesToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->is(IR_BASIC_BT)) {
            auto moreLambdaVariablesToFree = successorBlock->getLambdaVariablesToFree();
            allLambdaVariablesToFree->insert(
                allLambdaVariablesToFree->begin(),
                moreLambdaVariablesToFree->begin(),
                moreLambdaVariablesToFree->end()
            );
        }
    }
    return allLambdaVariablesToFree;
}

std::optional<IRFunctionReturnExpressionNode*> IRBlockNode::getReturnExpression() {
    return _returnExpression;
}

void IRBlockNode::setInsertionPointBeforeLastInstruction() {
    auto block = this->getLastSuccessorOrSelf();
    block->getBuilder()->get()->SetInsertPoint(block->getBlock()->getTerminator());
}

void IRBlockNode::setInsertionPointBeforeFirstInstruction() {
    this->getBuilder()->get()->SetInsertPoint(&*this->getBlock()->getFirstInsertionPt());
}

void IRBlockNode::resetInsertionPoint() {
    auto block = this->getLastSuccessorOrSelf();
    block->getBuilder()->get()->SetInsertPoint(block->getBlock());
}

void IRBlockNode::removeLastInstruction() {
    if (this->getBlock()->getTerminator()) {
        this->getBlock()->getTerminator()->eraseFromParent();
        this->getBuilder()->get()->SetInsertPoint(this->getBlock());
    }
}

void IRBlockNode::createSuccessor() {
    auto newBlock = new IRBlockNode(
        llvm::BasicBlock::Create(this->getBlock()->getContext(), "", this->getBlock()->getParent()),
        IR_BASIC_BT
    );
    newBlock->setParentBlock(this);
    _successors.push_back(newBlock);
}

std::vector<IRBlockNode*>* IRBlockNode::getSuccessors() {
    return &_successors;
}

std::vector<IRBlockNode*>* IRBlockNode::getAllSuccessors() {
    auto allSuccessors = new std::vector<IRBlockNode*>();
    for (auto successor : _successors) {
        allSuccessors->push_back(successor);
        auto successorsOfSuccessor = successor->getAllSuccessors();
        allSuccessors->insert(allSuccessors->end(), successorsOfSuccessor->begin(), successorsOfSuccessor->end());
    }
    return allSuccessors;
}

void IRBlockNode::addSuccessor(IRBlockNode* successorIrBlock) {
    _successors.push_back(successorIrBlock);
    successorIrBlock->setParentBlock(this);
    auto successorsOfSuccessorIrBlock = successorIrBlock->getSuccessors();
    for (int i = 0; i < successorsOfSuccessorIrBlock->size(); ++i) {
        _successors.push_back(successorsOfSuccessorIrBlock->at(i));
        successorsOfSuccessorIrBlock->at(i)->setParentBlock(this);
    }
}

IRBlockNode* IRBlockNode::getLastSuccessorOrSelf() {
    if (_successors.empty()) {
        return this;
    }
    return _successors.back();
}

std::optional<IRBlockNode*> IRBlockNode::getParentBlock() {
    return _parentBlock;
}

bool IRBlockNode::is(IRBlockType blockType) {
    return _type == blockType;
}

bool IRBlockNode::isOneOf(std::vector<IRBlockType> blockTypes) {
    return std::find(
            blockTypes.begin(),
            blockTypes.end(),
            _type) != blockTypes.end();
}

void IRBlockNode::setParentBlock(IRBlockNode* parentIRBlock) {
    _parentBlock = parentIRBlock;
}