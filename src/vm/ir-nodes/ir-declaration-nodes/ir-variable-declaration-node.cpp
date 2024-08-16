//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-variable-declaration-node.h"

IRVariableDeclarationNode::IRVariableDeclarationNode(ASTVariableDeclarationNode* astNode, IRInstructionNode* irValue, IRExpressionNode* irExpression) {
    _astNode = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
}
//
//void IRVariableDeclarationNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder) {
//    builder->get()->Insert(_irValue->getValue(), _node->getId());
//    auto irExpressionValue = _irExpression->insertSelfIntoBlock(builder, injectorMap);
//    builder->get()->CreateStore(irExpressionValue, _irValue->getValue());
//}

IRNodeType IRVariableDeclarationNode::getNodeType() {
    return IR_VARIABLE_DECLARATION_NODE;
}

std::string IRVariableDeclarationNode::toString() {
    return "IR_VARIABLE_DECLARATION_NODE";
}

void IRVariableDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}