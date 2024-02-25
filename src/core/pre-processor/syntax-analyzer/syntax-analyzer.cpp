//
// Created by Johny Georges on 2024-01-10.
//

#include "syntax-analyzer.h"
#include "reduce-node/reduce-node-factory.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"

SyntaxAnalyzer::SyntaxAnalyzer(TokenTable *tokenTable, LexicalAnalyzer* lexicalAnalyzer) {
    _tokenTable = tokenTable;
    _reducer = Reducer();
    _handle = Handle();
    _lexemeTransformer = LexemeTransformer();
    _stack = std::stack<ASTNode*>();
    _syntaxDfa = new SyntaxDfa();
    _lexicalAnalyzer = lexicalAnalyzer;
}

ASTFileNode* SyntaxAnalyzer::analyze(std::string &filePath) {
    auto fileNode = new ASTFileNode();
    _lexicalAnalyzer->start(filePath);
    while (true) {
        auto reduceNode = this->recognizeHandle();
        if (reduceNode) {
            this->reduceHandle(fileNode, reduceNode.value());
        } else {
            this->shift();
        }

        if (!_lexicalAnalyzer->hasMore()) {
            _handle.isEmpty() ? this->accept() : this->error();
            break;
        }
    }
    return fileNode;
}

std::optional<ReduceNode*> SyntaxAnalyzer::recognizeHandle() {
    _handle.print();
    if (_handle.isEmpty()) {
        return {};
    }
//    if (_handle.size() == 1 && _handle.isNodeTypeAt(0, AST_TERMINATOR_NODE)) {
//        if (_stack.empty()) {
//            _handle.clear();
//            return {};
//        } else if (_stack.size() == 1) {
//            _handle.append(_stack.top());
//            auto reduceNode = ReduceNodeFactory::create(_handle, _handle.size(), _stack.top()->getNodeType());
//            _stack.pop();
//            return reduceNode;
//        } else {
//            while (!_stack.empty()) {
//                _handle.prepend(_stack.top());
//                _stack.pop();
//            }
//            return _syntaxDfa->recognize(_handle);
//        }
//    }
    return _syntaxDfa->recognize(_handle);
}

void SyntaxAnalyzer::shift() {
    auto nextLexeme = _lexicalAnalyzer->next();
    if (nextLexeme) {
        _handle.append(this->_lexemeTransformer.transform(nextLexeme.value()));
    }
}

void SyntaxAnalyzer::reduceHandle(ASTFileNode* fileNode, ReduceNode* reduceNode) {
    Logger::log("handle size", _handle.size(), "| num nodes to reduce:", reduceNode->getNumReducedNodes(), " | target ast node type: ", reduceNode->getTargetAstNodeType());
    auto reducedNode = _reducer.reduce(_handle, reduceNode);
    auto isReducedNodeDeclarationNode = ASTNodeUtils::isDeclarationNode(reducedNode);
    if (isReducedNodeDeclarationNode) {
        Logger::log("pushing node to file node:", reducedNode->toString());
        fileNode->append(reducedNode);
    } else {
        Logger::log("pushing node to stack:", reducedNode->toString());
        _stack.push(reducedNode);
    }
    auto lastNode = _handle.last().value();
    _handle.removeFirstNodes(reduceNode->getNumReducedNodes());
    if (_handle.isEmpty() && !isReducedNodeDeclarationNode && lastNode->is(AST_TERMINATOR_NODE)) {
        Logger::log("recycling stack nodes...");
        while (!_stack.empty()) {
                _handle.prepend(_stack.top());
                _stack.pop();
        }
    }
}

void SyntaxAnalyzer::accept() {
    Logger::log("file accepted");
}

void SyntaxAnalyzer::error() {
    Logger::log("file errored");
}