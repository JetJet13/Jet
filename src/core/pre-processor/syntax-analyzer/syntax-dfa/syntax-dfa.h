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
    DFA _dfa;
    void init();
    void initVarDefinition(std::shared_ptr<DFANode> varDefinition);
    void initVarInit(std::shared_ptr<DFANode> varInitNode, ASTNodeType targetNodeType);
    void initFunction(std::shared_ptr<DFANode> functionNode);
    void initProcedure(std::shared_ptr<DFANode> procedureNode);
    void initEnum(std::shared_ptr<DFANode> enumNode);
    void initCustomType(std::shared_ptr<DFANode> typeKeyword);
    void initIf(std::shared_ptr<DFANode> ifNode);
    void initElse(std::shared_ptr<DFANode> elseNode);
    void initElseIf(std::shared_ptr<DFANode> elseIfNode);
    void initWhile(std::shared_ptr<DFANode> whileNode);
    void initFor(std::shared_ptr<DFANode> forNode);
    void initAccessModifier(std::shared_ptr<DFANode> accessModifier);
    void initClassPropertyDefinition(std::shared_ptr<DFANode> classPropertyDefinition);
    void initClassPropertyDefinitionWithType(std::shared_ptr<DFANode> classPropertyDefinitionWithType);
    void setupTransitionsWithTarget(std::shared_ptr<DFANode> node, ASTNodeType targetNodeType, std::vector<ASTNodeType> nodeTypes);
public:
    SyntaxDfa();
    DFA* getDFA();
    std::optional<std::shared_ptr<DFANode>> findStartNode(std::optional<std::shared_ptr<ASTNode>> astNode);
};

#endif //JETLANG_SYNTAX_DFA_H
