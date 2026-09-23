//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_RECOGNIZER_RESULT_H
#define JETLANG_RECOGNIZER_RESULT_H

#include "../../../ast/ast-nodes/ast-node.h"
#include "types/recognizer-action.h"

class RecognizerResult {
private:
    RecognizerAction _recognizerAction;
    ASTNodeType _targetAstNodeType;
    uint64_t _numReducedNodes;
public:
    RecognizerResult(RecognizerAction recognizerAction, uint64_t numReducedNodes = 0, ASTNodeType targetAstNodeType = AST_NULL_NODE);
    ASTNodeType getTargetAstNodeType();
    int getNumReducedNodes();
    bool reduce();
    bool shift();
    bool pop();
};

#endif //JETLANG_RECOGNIZER_RESULT_H
