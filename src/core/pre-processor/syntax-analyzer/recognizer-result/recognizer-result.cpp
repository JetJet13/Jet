//
// Created by Johny Georges on 2024-02-08.
//

#include "recognizer-result.h"

RecognizerResult::RecognizerResult(RecognizerAction recognizerAction, int numReducedNodes, ASTNodeType targetAstNodeType) {
    _recognizerAction = recognizerAction;
    _targetAstNodeType = targetAstNodeType;
    _numReducedNodes = numReducedNodes;
}

ASTNodeType RecognizerResult::getTargetAstNodeType() {
    return _targetAstNodeType;
}

int RecognizerResult::getNumReducedNodes() {
    return _numReducedNodes;
}

bool RecognizerResult::reduce() {
    return _recognizerAction == RECOGNIZER_ACTION_REDUCE;
}

bool RecognizerResult::shift() {
    return _recognizerAction == RECOGNIZER_ACTION_SHIFT;
}

bool RecognizerResult::pop() {
    return _recognizerAction == RECOGNIZER_ACTION_POP;
}