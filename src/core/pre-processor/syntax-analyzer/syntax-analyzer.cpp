//
// Created by Johny Georges on 2024-01-10.
//

#include "syntax-analyzer.h"
#include "../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "type-signature-generator/type-signature-generator.h"

SyntaxAnalyzer::SyntaxAnalyzer(TokenTable *tokenTable, LexicalAnalyzer* lexicalAnalyzer) {
    _tokenTable = tokenTable;
    _reducer = Reducer(new TypeSignatureGenerator(_tokenTable));
    _handle = Handle();
    _lexemeTransformer = LexemeTransformer();
    _modeStack = std::stack<SyntaxAnalyzerMode>();
    _scopeStack = std::stack<ASTBlockNode*>();
    _recognizeStack = std::stack<std::stack<ASTNode*>*>();
    _recognizer = new Recognizer();
    _lexicalAnalyzer = lexicalAnalyzer;
}

ASTFileNode* SyntaxAnalyzer::analyze(std::string &filePath) {
    _scopeStack.push(new ASTBlockNode());
    _recognizeStack.push(new std::stack<ASTNode*>());
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

        if (_recognizeStack.empty()) {
            throw std::logic_error("REDUCE NODE IS CLASS BLOCK!");
        }

        if (_recognizeStack.top()->empty() && !_lexicalAnalyzer->hasMore()) {
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
    this->prepHandleForRecognizer();
    _handle.print();
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
        _recognizeStack.push(new std::stack<ASTNode*>());
    } else if (reducedNode->is(AST_BLOCK_END_NODE)) {
        auto blockNode = _scopeStack.top();
        _scopeStack.pop();
        _recognizeStack.pop();
        if (_recognizeStack.empty()) {
            throw std::logic_error("recognizeStack is empty");
        }
        _recognizeStack.top()->push(blockNode);
    } else if (ASTNodeUtils::isDeclarationNode(reducedNode)) {
        Logger::log("pushing node to latest scope node:", reducedNode->toString());
        if (!_scopeStack.empty()) {
            _scopeStack.top()->addContent(reducedNode);
        } else {
            throw std::logic_error("scope stack missing block!");
        }
    } else {
        Logger::log("pushing node to stack:", reducedNode->toString());
        _recognizeStack.top()->push(reducedNode);
    }

    _handle.removeFirstNodes(recognizerResult->getNumReducedNodes());
    if (ASTNodeUtils::isDeclarationNode(reducedNode) && _handle.isTerminatorOnlyNode()) {
        _handle.clear();
    }
}

void SyntaxAnalyzer::popFromStack() {
    if (_recognizeStack.top()->empty()) {
        throw std::logic_error("stack is empty. Nothing to pop.");
    }
    Logger::log("popping from stack...");
    _handle.prepend(_recognizeStack.top()->top());
    _recognizeStack.top()->pop();
}

void SyntaxAnalyzer::accept() {
    Logger::log("file accepted");
}

void SyntaxAnalyzer::error() {
    Logger::log("file errored");
}

void SyntaxAnalyzer::prepHandleForRecognizer() {
    if (_modeStack.empty()) {
        throw std::invalid_argument("modeStack is empty!");
    }

    if (!_recognizeStack.top()->empty()) {
        _handle.setLastReducedNode(_recognizeStack.top()->top());
    } else {
        _handle.clearLastReducedNode();
    }

    if (_recognizeStack.top()->empty() && _handle.isTerminatorOnlyNode()) {
        _handle.clear();
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
        Logger::log("group enclosed..removing brackets and popping group mode");
        _handle.removeFirstNode();
        _handle.removeLastNode();
        _modeStack.pop();
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
        case AST_GROUP_START_NODE:
            Logger::log("pushing mode: GROUP_MODE");
            _modeStack.push(SA_GROUP_MODE);
            break;
        case AST_STRUCT_START_NODE:
            Logger::log("pushing mode: STRUCT_MODE");
            _modeStack.push(SA_STRUCT_MODE);
            break;
        case AST_FUNCTION_PARAMETER_LIST_START_NODE:
            Logger::log("pushing mode: FUNCTION_PARAMETER_LIST_MODE");
            _modeStack.push(SA_FUNCTION_PARAMETER_LIST_MODE);
            break;
        case AST_TYPE_PARAMETER_LIST_START_NODE:
            Logger::log("pushing mode: TYPE_PARAMETER_LIST_MODE");
            _modeStack.push(SA_TYPE_PARAMETER_LIST_MODE);
            break;
        case AST_FUNCTION_ARGUMENT_LIST_START_NODE:
            Logger::log("pushing mode: FUNCTION_ARGUMENT_LIST_MODE");
            _modeStack.push(SA_FUNCTION_ARGUMENT_LIST_MODE);
            break;
        case AST_ENUM_KEY_VALUE_LIST_START_NODE:
            Logger::log("pushing mode: ENUM_KEY_VALUE_LIST_MODE");
            _modeStack.push(SA_ENUM_KEY_VALUE_LIST_MODE);
            break;
        case AST_MODULE_LIST_START_NODE:
            Logger::log("pushing mode: MODULE_LIST_MODE");
            _modeStack.push(SA_MODULE_LIST_MODE);
            break;
        case AST_IMPORT_MODULE_LIST_START_NODE:
            Logger::log("pushing mode: IMPORT_MODULE_LIST_MODE");
            _modeStack.push(SA_IMPORT_MODULE_LIST_MODE);
            break;
        case AST_TUPLE_LIST_START_NODE:
            Logger::log("pushing mode: TUPLE_LIST_MODE");
            _modeStack.push(SA_TUPLE_LIST_MODE);
            break;
        case AST_IF_NODE:
        case AST_ELSE_IF_NODE:
        case AST_WHILE_NODE:
        case AST_FOR_IN_NODE:
            Logger::log("pushing mode: CONTROL_FLOW_MODE");
            _modeStack.push(SA_CONTROL_FLOW_MODE);
            break;
        case AST_BLOCK_NODE:
        case AST_STRUCT_EXPRESSION_NODE:
        case AST_FUNCTION_PARAMETER_LIST_NODE:
        case AST_FUNCTION_ARGUMENT_LIST_NODE:
        case AST_ENUM_KEY_VALUE_LIST_NODE:
        case AST_FUNCTION_LAMBDA_TYPE_PARAMETER_LIST_NODE:
        case AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE:
        case AST_TUPLE_TYPE_NODE:
        case AST_ARRAY_TYPE_NODE:
        case AST_TUPLE_LIST_NODE:
        case AST_MODULE_LIST_NODE:
        case AST_IMPORT_MODULE_LIST_NODE:
        case AST_CONTROL_FLOW_CONDITION_NODE:
        case AST_FOR_SOURCE_NODE:
            Logger::log("popping mode:", _modeStack.top());
            _modeStack.pop();
            break;
        default:
            break;
    }

    if (astNodeType == AST_COLON_NODE && _modeStack.top() == SA_GROUP_MODE) {
        Logger::log("replacing GROUP_MODE with FUNCTION_PARAMETER_LIST_MODE");
        _modeStack.pop();
        _modeStack.push(SA_FUNCTION_PARAMETER_LIST_MODE);
    }
}