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
    _modeStack = std::stack<SyntaxAnalyzerMode>();
    _scopeStack = std::stack<ASTBlockNode*>();
    _stack = std::stack<ASTNode*>();
    _recognizer = new Recognizer();
    _lexicalAnalyzer = lexicalAnalyzer;
}

ASTFileNode* SyntaxAnalyzer::analyze(std::string &filePath) {
    _scopeStack.push(new ASTBlockNode());
    _modeStack.push(SA_NORMAL_MODE);
    _lexicalAnalyzer->start(filePath);
    auto numLoops = 0;
    while (true) {
        if (numLoops == 10000) {
            throw std::logic_error("too many loops!");
        }
        auto recognizerResult = this->recognizeHandle();
        if (recognizerResult->reduce()) {
            this->updateModeIfNecessary(recognizerResult->getTargetAstNodeType());
            this->reduceHandle(recognizerResult);
        } else if (recognizerResult->pop()) {
            this->popFromStack();
        } else if (recognizerResult->shift()){
            this->shift();
        }

        if (_stack.empty() && !_lexicalAnalyzer->hasMore()) {
            if (_handle.isEmpty()) {
                this->accept();
                break;
            }
        }
        numLoops++;
    }
    return this->buildFileNode();
}

RecognizerResult* SyntaxAnalyzer::recognizeHandle() {
    Logger::log("recognize");
    _handle.print();
    this->prepHandleForRecognizer();
    return _recognizer->recognize(&_handle);
}

void SyntaxAnalyzer::shift() {
    Logger::log("shift");
    auto nextLexeme = _lexicalAnalyzer->next();
    if (nextLexeme) {
        _handle.append(this->_lexemeTransformer.transform(nextLexeme.value()));
    }
}

void SyntaxAnalyzer::reduceHandle(RecognizerResult* recognizerResult) {
    Logger::log("reduce");
    Logger::log("handle size", _handle.size(), "| num nodes to reduce:", recognizerResult->getNumReducedNodes(), " | target ast node type: ", recognizerResult->getTargetAstNodeType());
    auto reducedNode = _reducer.reduce(_handle, recognizerResult);
    if (reducedNode->is(AST_BLOCK_START_NODE)) {
        _scopeStack.push(new ASTBlockNode());
    } else if (reducedNode->is(AST_BLOCK_END_NODE)) {
        auto blockNode = _scopeStack.top();
        _scopeStack.pop();
        _stack.push(blockNode);
    } else if (ASTNodeUtils::isDeclarationNode(reducedNode)) {
        Logger::log("pushing node to latest scope node:", reducedNode->toString());
        if (!_scopeStack.empty()) {
            _scopeStack.top()->addContent(reducedNode);
        } else {
            throw std::logic_error("scope stack missing block!");
        }
    } else {
        Logger::log("pushing node to stack:", reducedNode->toString());
        _stack.push(reducedNode);
    }

    _handle.removeFirstNodes(recognizerResult->getNumReducedNodes());
    if (ASTNodeUtils::isDeclarationNode(reducedNode) && _handle.isTerminatorOnlyNode()) {
        _handle.clear();
    }
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
                                    _modeStack.top()));
    }

    if (_handle.isGroupEnclosed()) {
        Logger::log("group enclosed..removing brackets");
        _handle.removeFirstNode();
        _handle.removeLastNode();
    }
}

ASTFileNode* SyntaxAnalyzer::buildFileNode() {
    auto fileNode = new ASTFileNode(_scopeStack.top());
    _scopeStack.pop();
    return fileNode;
}

void SyntaxAnalyzer::updateModeIfNecessary(ASTNodeType astNodeType) {
    switch (astNodeType) {
        case AST_BLOCK_START_NODE:
            Logger::log("pushing mode: BLOCK_MODE");
            _modeStack.push(SA_BLOCK_MODE);
            break;
        case AST_STRUCT_START_NODE:
            Logger::log("pushing mode: STRUCT_MODE");
            _modeStack.push(SA_STRUCT_MODE);
            break;
        case AST_FUNCTION_PARAMETER_LIST_START_NODE:
            Logger::log("pushing mode: FUNCTION_PARAMETER_LIST_MODE");
            _modeStack.push(SA_FUNCTION_PARAMETER_LIST_MODE);
            break;
        case AST_FUNCTION_ARGUMENT_LIST_START_NODE:
            Logger::log("pushing mode: FUNCTION_ARGUMENT_LIST_MODE");
            _modeStack.push(SA_FUNCTION_ARGUMENT_LIST_MODE);
            break;
        case AST_ENUM_KEY_VALUE_LIST_START_NODE:
            Logger::log("pushing mode: ENUM_KEY_VALUE_LIST_MODE");
            _modeStack.push(SA_ENUM_KEY_VALUE_LIST_MODE);
            break;
        case AST_BLOCK_NODE:
        case AST_STRUCT_EXPRESSION_NODE:
        case AST_FUNCTION_PARAMETER_LIST_NODE:
        case AST_FUNCTION_ARGUMENT_LIST_NODE:
        case AST_ENUM_KEY_VALUE_LIST_NODE:
            Logger::log("popping mode:", _modeStack.top());
            _modeStack.pop();
            break;
        default:
            break;
    }
}