//
// Created by Johny Georges on 2024-02-14.
//

#ifndef JETLANG_SYNTAX_DFA_H
#define JETLANG_SYNTAX_DFA_H

#include <vector>
#include "../handle/handle.h"
#include "../../../dfa/dfa.h"
#include "../reduce-node/reduce-node.h"

class SyntaxDfa {
private:
    DFA* _dfa;
    void init();
public:
    SyntaxDfa();
    std::optional<ReduceNode*> recognize(Handle handle);
    DFA* getDFA();
};

#endif //JETLANG_SYNTAX_DFA_H
