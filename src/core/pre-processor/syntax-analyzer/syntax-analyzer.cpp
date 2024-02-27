//
// Created by Johny Georges on 2024-01-10.
//

#include "syntax-analyzer.h"
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
        } else if (this->isTerminatorMode()) {
            this->popFromStack();
        } else {
            this->shift();
        }

        if (!this->isTerminatorMode() && !_lexicalAnalyzer->hasMore()) {
            _handle.isEmpty() ? this->accept() : this->error();
            break;
        }
    }
    return fileNode;
}

std::optional<ReduceNode*> SyntaxAnalyzer::recognizeHandle() {
    Logger::log("recognize");
    _handle.print();
    if (_handle.isEmpty() ||
        (_handle.size() == 1 && this->isTerminatorMode())) {
        return {};
    }
    this->prepHandleForRecognizer();
    return _syntaxDfa->recognize(_handle);
}

void SyntaxAnalyzer::shift() {
    Logger::log("shift");
    auto nextLexeme = _lexicalAnalyzer->next();
    if (nextLexeme) {
        _handle.append(this->_lexemeTransformer.transform(nextLexeme.value()));
    }
}

void SyntaxAnalyzer::reduceHandle(ASTFileNode* fileNode, ReduceNode* reduceNode) {
    Logger::log("reduce");
    Logger::log("handle size", _handle.size(), "| num nodes to reduce:", reduceNode->getNumReducedNodes(), " | target ast node type: ", reduceNode->getTargetAstNodeType(), " | include prefix: ", reduceNode->includePrefix());
    if (reduceNode->includePrefix()) {
        this->popFromStack();
    }
    auto reducedNode = _reducer.reduce(_handle, reduceNode);
    auto isReducedNodeDeclarationNode = ASTNodeUtils::isDeclarationNode(reducedNode);
    if (isReducedNodeDeclarationNode) {
        Logger::log("pushing node to file node:", reducedNode->toString());
        fileNode->append(reducedNode);
    } else {
        Logger::log("pushing node to stack:", reducedNode->toString());
        _stack.push(reducedNode);
    }
    _handle.removeFirstNodes(reduceNode->getNumReducedNodes());
}

void SyntaxAnalyzer::popFromStack() {
    if (_stack.empty()) {
        throw std::logic_error("stack is empty. Nothing to pop.");
    }
    Logger::log("popping from stack...");
    _handle.prepend(_stack.top());
    _stack.pop();
}

void SyntaxAnalyzer::accept() {
    Logger::log("file accepted");
}

void SyntaxAnalyzer::error() {
    Logger::log("file errored");
}

bool SyntaxAnalyzer::isTerminatorMode() {
    return !_handle.isEmpty() && _handle.last().value()->is(AST_TERMINATOR_NODE);
}

void SyntaxAnalyzer::prepHandleForRecognizer() {
    if (!_stack.empty()) {
        _handle.setLastReducedNode(_stack.top());
    } else {
        _handle.clearLastReducedNode();
    }

    auto peekNode = _lexemeTransformer.transform(_lexicalAnalyzer->peek());
    if (peekNode) {
        _handle.setPeekNode(peekNode);
    } else {
        _handle.clearPeekNode();
    }
}