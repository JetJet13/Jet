//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-control-flow-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTControlFlowBlockNode::ASTControlFlowBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTNode*> contents, ASTBlockEndNode* blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        _contents.push_back(content);
        _children.push_back(content);
    }
}

std::vector<ASTNode*>* ASTControlFlowBlockNode::getContents() {
    return &_contents;
}

bool ASTControlFlowBlockNode::hasReturnExpression() {
    for (auto statement: _contents) {
        if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            return true;
        }
    }
    return false;
}

ASTNodeType ASTControlFlowBlockNode::getNodeType() {
    return AST_CONTROL_FLOW_BLOCK_NODE;
}

std::string ASTControlFlowBlockNode::toString() {
    return "CONTROL_FLOW_BLOCK";
}

bool ASTControlFlowBlockNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTControlFlowBlockNode*)other;
    for (int i = 0; i < _contents.size(); ++i) {
        if (!_contents[i]->isSameAs(otherNode->getContents()->at(i))) {
            return false;
        }
    }
    return true;
}

void ASTControlFlowBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}

std::string ASTControlFlowBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_blockStartNode);

    for (auto content : _contents) {
        sourceCodeBuilder.addWithNewLine(content);
    }

    sourceCodeBuilder.addWithNewLine(_blockEndNode);
    return sourceCodeBuilder.build();
}