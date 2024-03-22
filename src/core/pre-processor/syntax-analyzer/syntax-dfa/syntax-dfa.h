//
// Created by Johny Georges on 2024-02-14.
//

#ifndef JETLANG_SYNTAX_DFA_H
#define JETLANG_SYNTAX_DFA_H

#include <vector>
#include "../handle/handle.h"
#include "../../../dfa/dfa.h"
#include "../recognizer-result/recognizer-result.h"

class SyntaxDfa {
private:
    DFA* _dfa;
    void init();
    void initVarType(DFANode* varTypeNode);
    void initVarInit(DFANode* varInitNode);
    void initFunction(DFANode* functionNode);
    void initProcedure(DFANode* procedureNode);
public:
    SyntaxDfa();
    RecognizerResult* recognize(Handle handle);
    DFA* getDFA();
};

#endif //JETLANG_SYNTAX_DFA_H
