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
    void initVarDefinition(DFANode* varDefinition);
    void initVarInit(DFANode* varInitNode);
    void initFunction(DFANode* functionNode);
    void initProcedure(DFANode* procedureNode);
    void initEnum(DFANode* enumNode);
    void initIf(DFANode* ifNode);
    void initElse(DFANode* elseNode);
    void initElseIf(DFANode* elseIfNode);
    void initWhile(DFANode* whileNode);
    void initFor(DFANode* forNode);
public:
    SyntaxDfa();
    DFA* getDFA();
    std::optional<DFANode*> findStartNode(std::optional<ASTNode*> astNode);
};

#endif //JETLANG_SYNTAX_DFA_H
