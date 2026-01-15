//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-block-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "../ast-scoped-block-node.h"

ASTFunctionBlockNode::ASTFunctionBlockNode(ASTBlockStartNode* blockStartNode, std::vector<ASTNode*> contents, ASTBlockEndNode* blockEndNode) {
    _blockStartNode = blockStartNode;
    _blockEndNode = blockEndNode;
    _children.push_back(_blockStartNode);
    _contents = std::vector<ASTNode*>();
    _returnStatements = std::vector<ASTFunctionReturnExpressionNode*>();
    for (auto content: contents) {
        _contents.push_back(content);
        _children.push_back(content);
        if (content->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            _returnStatements.push_back((ASTFunctionReturnExpressionNode*)content);
        }
        if (content->isScopedBlockNode()) {
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

std::vector<ASTNode*>* ASTFunctionBlockNode::getContents() {
    return &_contents;
}

std::vector<ASTFunctionReturnExpressionNode*>* ASTFunctionBlockNode::getReturnStatements() {
    return &_returnStatements;
}

bool ASTFunctionBlockNode::hasReturnExpression() {
    return !_returnStatements.empty();
}

Position* ASTFunctionBlockNode::getStartPosition() {
    return _blockStartNode->getStartPosition();
}

Position* ASTFunctionBlockNode::getEndPosition() {
    return _blockEndNode->getEndPosition();
}

ASTNodeType ASTFunctionBlockNode::getNodeType() {
    return AST_FUNCTION_BLOCK_NODE;
}

std::string ASTFunctionBlockNode::toString() {
    return "FUNCTION_BLOCK";
}

bool ASTFunctionBlockNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionBlockNode*)other;
    for (unsigned long i = 0; i < _contents.size(); ++i) {
        if (!_contents[i]->isSameAs(otherNode->getContents()->at(i))) {
            return false;
        }
    }
    return true;
}

void ASTFunctionBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}

std::string ASTFunctionBlockNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_blockStartNode);

    for (auto content : _contents) {
        sourceCodeBuilder.add(content);
    }

    sourceCodeBuilder.add(_blockEndNode);
    return sourceCodeBuilder.build();
}