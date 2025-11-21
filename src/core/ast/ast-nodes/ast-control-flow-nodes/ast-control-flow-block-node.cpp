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
    _returnStatements = std::vector<ASTFunctionReturnExpressionNode*>();
    _children.push_back(_blockStartNode);
    for (auto content: contents) {
        _contents.push_back(content);
        _children.push_back(content);
        if (content->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            _returnStatements.push_back((ASTFunctionReturnExpressionNode*)content);
        } else if (content->isScopedBlockNode()) {
            auto scopeBlockNodeReturnStatements = ((ASTScopedBlockNode*)content)->getReturnStatements();
            _returnStatements.insert(
                    _returnStatements.end(),
                    scopeBlockNodeReturnStatements->begin(),
                    scopeBlockNodeReturnStatements->end()
            );
        }
    }
    _children.push_back(_blockEndNode);
}

std::vector<ASTNode*>* ASTControlFlowBlockNode::getContents() {
    return &_contents;
}

std::vector<ASTFunctionReturnExpressionNode*>* ASTControlFlowBlockNode::getReturnStatements() {
    return &_returnStatements;
}

bool ASTControlFlowBlockNode::hasReturnExpression() {
   return !_returnStatements.empty();
}

Position* ASTControlFlowBlockNode::getStartPosition() {
    return _blockStartNode->getStartPosition();
}

Position* ASTControlFlowBlockNode::getEndPosition() {
    return _blockEndNode->getEndPosition();
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
        sourceCodeBuilder.add(content);
    }

    sourceCodeBuilder.add(_blockEndNode);
    return sourceCodeBuilder.build();
}