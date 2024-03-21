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
    auto numLoops = 0;
    while (true) {
        if (numLoops == 20000) {
            throw std::logic_error("too many loops!");
        }
        auto recognizerResult = this->recognizeHandle();
        if (recognizerResult->reduce()) {
            this->reduceHandle(fileNode, recognizerResult);
        } else if (recognizerResult->pop()) {
            this->popFromStack();
        } else if (recognizerResult->shift()){
            this->shift();
        }

        this->disableTerminatorModeIfNecessary();
        this->disableGroupingModeIfNecessary();
        this->disableArrayModeIfNecessary();
        this->disableBlockModeIfNecessary();
        this->disableStructModeIfNecessary();
        this->disableFunctionParameterListModeIfNecessary();

        if (!_handle.isTerminatorMode() && !_lexicalAnalyzer->hasMore()) {
            _handle.isEmpty() ? this->accept() : this->error();
            break;
        }
        numLoops++;
    }
    return fileNode;
}

RecognizerResult* SyntaxAnalyzer::recognizeHandle() {
    Logger::log("recognize");
    _handle.print();
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

void SyntaxAnalyzer::reduceHandle(ASTFileNode* fileNode, RecognizerResult* recognizerResult) {
    Logger::log("reduce");
    Logger::log("handle size", _handle.size(), "| num nodes to reduce:", recognizerResult->getNumReducedNodes(), " | target ast node type: ", recognizerResult->getTargetAstNodeType());
    auto reducedNode = _reducer.reduce(_handle, recognizerResult);
    if (ASTNodeUtils::isDeclarationNode(reducedNode)) {
        Logger::log("pushing node to file node:", reducedNode->toString());
        fileNode->append(reducedNode);
    } else {
        Logger::log("pushing node to stack:", reducedNode->toString());
        _stack.push(reducedNode);
    }
    _handle.removeFirstNodes(recognizerResult->getNumReducedNodes());
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

    for (int i = 0; i < _handle.size(); i++) {
            _handle.replace(i,
                            _handle.at(i).value()->transformIfNecessary(
                                    _handle.getPrevNodeFor(i),
                                    _handle.getNextNodeFor(i),
                                    _handle.getMode()));
    }

    if (_handle.isGroupEnclosed()) {
        Logger::log("group enclosed..removing brackets");
        _handle.removeFirstNode();
        _handle.removeLastNode();
    }
}

void SyntaxAnalyzer::disableTerminatorModeIfNecessary() {
    if (_handle.isTerminatorMode() && _stack.empty() && _handle.isTerminatorOnlyNode()) {
        Logger::log("disabling terminator mode");
        _handle.clear();
    }
}

void SyntaxAnalyzer::disableGroupingModeIfNecessary() {
    if (_handle.isGroupingMode() && _stack.empty()) {
        Logger::log("disabling grouping mode");
        _handle.clear();
    }
}

void SyntaxAnalyzer::disableArrayModeIfNecessary() {
    if (_handle.isArrayMode() && _stack.empty()) {
        Logger::log("disabling array mode");
        _handle.clear();
    }
}

void SyntaxAnalyzer::disableBlockModeIfNecessary() {
    if (_handle.isBlockMode() && _stack.empty()) {
        Logger::log("disabling brace mode");
        _handle.clear();
    }
}

void SyntaxAnalyzer::disableStructModeIfNecessary() {
    if (_handle.isStructMode() && _stack.empty()) {
        Logger::log("disabling struct mode");
        _handle.clear();
    }
}

void SyntaxAnalyzer::disableFunctionParameterListModeIfNecessary() {
    if (_handle.isFunctionParameterListMode() && _stack.empty()) {
        Logger::log("disabling function parameter list mode");
        _handle.clear();
    }
}