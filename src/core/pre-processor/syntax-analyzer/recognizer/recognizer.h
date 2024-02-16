//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_RECOGNIZER_H
#define JETLANG_RECOGNIZER_H

#include <deque>
#include "../../../ast/ast-nodes/ast-node.h"
#include "../reduce-node/reduce-node.h"
#include "../handle/handle.h"

// This class will be responsible
// for recognizing handles (i.e. when we need to reduce the handle)
// it will need to be a DFA (deterministic finite automata state machine)
class Recognizer {
private:
    Handle* _handle;
    std::optional<ReduceNode*> recognizeVariableTypeNode();
    std::optional<ReduceNode*> recognizeIntLiteralNode();
    std::optional<ReduceNode*> isLiteralAssignment();
public:
    Recognizer(Handle* handle);
    std::optional<ReduceNode*> recognize();
};

#endif //JETLANG_RECOGNIZER_H
