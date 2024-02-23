//
// Created by Johny Georges on 2024-01-10.
//

#include "syntax-analyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer(TokenTable *tokenTable, LexicalAnalyzer* lexicalAnalyzer) {
    _tokenTable = tokenTable;
    _reducer = Reducer();
    _handle = Handle();
    _lexemeTransformer = LexemeTransformer();
    _stack = std::stack<ASTNode*>();
    _syntaxDfa = new SyntaxDfa();
    _lexicalAnalyzer = lexicalAnalyzer;
}

void SyntaxAnalyzer::analyze() {
    while (true) {
        auto reduceNode = this->recognizeHandle();
        if (reduceNode) {
            this->reduceHandle(reduceNode.value());
        } else {
            this->shift();
        }

        if (!_lexicalAnalyzer->hasMore()) {
            _handle.isEmpty() ? this->accept() : this->error();
            break;
        }
    }
}

std::optional<ReduceNode*> SyntaxAnalyzer::recognizeHandle() {
    if (_handle.isEmpty()) {
        return {};
    }
    if (_handle.size() == 1 && _handle.isNodeTypeAt(0, AST_TERMINATOR_NODE)) {
        if (_stack.empty()) {
            _handle.clear();
            return {};
        } else if (_stack.size() == 1) {
            _handle.push(_stack.top());
            auto reduceNode = new ReduceNode(1, _stack.top()->getNodeType());
            _stack.pop();
            return reduceNode;
        } else {
            while (!_stack.empty()) {
                _handle.push(_stack.top());
                _stack.pop();
            }
            return _syntaxDfa->recognize(_handle);
        }
    }
    return _syntaxDfa->recognize(_handle);
}

void SyntaxAnalyzer::shift() {
    auto nextLexeme = _lexicalAnalyzer->next();
    if (nextLexeme) {
        _handle.push(this->_lexemeTransformer.transform(nextLexeme.value()));
    }
}

void SyntaxAnalyzer::reduceHandle(ReduceNode* reduceNode) {
    _stack.push(_reducer.reduce(_handle, reduceNode));
    _handle.removeFirstNodes(reduceNode->getNumReducedNodes());
}

void SyntaxAnalyzer::accept() {

}

void SyntaxAnalyzer::error() {

}
