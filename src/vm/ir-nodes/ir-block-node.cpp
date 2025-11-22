//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-block-node.h"
#include "../../shared/utils/logger/logger.h"

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

bool IRBlockNode::hasBranchStatement() {
    return llvm::isa<llvm::BranchInst>(_irValue->back());
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

void IRBlockNode::addExpressionToFree(IRExpressionNode* expressionNode) {
    _expressionsToFree.push_back(expressionNode);
}

std::vector<IRExpressionNode*>* IRBlockNode::getExpressionsToFree() {
    return &_expressionsToFree;
}

void IRBlockNode::addReturnExpression(IRFunctionReturnExpressionNode* returnExpressionNode) {
    _returnExpression = returnExpressionNode;
}

void IRBlockNode::addVariableToFree(IRVariableDeclarationNode* variableNode) {
    _variablesToFree.push_back(variableNode);
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getVariablesToFree() {
    return &_variablesToFree;
}

std::vector<IRVariableDeclarationNode*>* IRBlockNode::getAllVariablesToFree() {
    auto allVariablesToFree = new std::vector<IRVariableDeclarationNode*>();
    allVariablesToFree->insert(allVariablesToFree->begin(), _variablesToFree.begin(), _variablesToFree.end());
    for (auto successorBlock : _successors) {
        if (successorBlock->isBasicBlock()) {
            auto moreVariablesToFree = successorBlock->getVariablesToFree();
            allVariablesToFree->insert(
                    allVariablesToFree->end(),
                    moreVariablesToFree->begin(),
                    moreVariablesToFree->end()
            );

        }
    }
    return allVariablesToFree;
}

std::optional<IRFunctionReturnExpressionNode*> IRBlockNode::getReturnExpression() {
    return _returnExpression;
}

void IRBlockNode::setInsertionPointBeforeReturn() {
    auto block = this->getLastSuccessorOrSelf();
    block->getBuilder()->get()->SetInsertPoint(block->getBlock()->getTerminator());
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

bool IRBlockNode::containsInstruction(IRInstructionNode* irInstructionNode) {
    if (_parentBlock) {
        return _parentBlock.value()->containsInstruction(irInstructionNode);
    }

    auto instruction = llvm::cast<llvm::Instruction>(irInstructionNode->getValue());
    if (instruction->getParent() == _irValue) {
        return true;
    }
    for (auto successorBlock : _successors) {
        if (instruction->getParent() == successorBlock->getBlock()) {
            return true;
        }
    }
    return false;
}

bool IRBlockNode::isBasicBlock() {
    return _type == IR_BASIC_BT;
}

bool IRBlockNode::isIfBlock() {
    return _type == IR_IF_BT;
}

bool IRBlockNode::isIfThenBlock() {
    return _type == IR_IF_THEN_BT;
}

bool IRBlockNode::isIfElseBlock() {
    return _type == IR_IF_ELSE_BT;
}

bool IRBlockNode::isWhileBlock() {
    return _type == IR_WHILE_BT;
}

bool IRBlockNode::isForLoopBlock() {
    return _type == IR_FOR_LOOP_BT;
}

bool IRBlockNode::isForInBlock() {
    return _type == IR_FOR_IN_BT;
}

void IRBlockNode::setParentBlock(IRBlockNode* parentIRBlock) {
    _parentBlock = parentIRBlock;
}