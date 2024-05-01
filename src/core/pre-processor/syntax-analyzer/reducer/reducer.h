//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_REDUCER_H
#define JETLANG_REDUCER_H

#include <vector>
#include "../../../lexeme/lexeme.h"
#include "../../../ast/ast-nodes/ast-node.h"
#include "../handle/handle.h"
#include "../recognizer-result/recognizer-result.h"
#include "reducer-strategies/reducer-strategy.h"
#include "../type-signature-generator/type-signature-generator.h"

// This class will be responsible
// for reducing handles (i.e. determine what to reduce the handle to)
class Reducer {
private:
    TypeSignatureGenerator* _typeSignatureGenerator;
    std::unordered_map<ASTNodeType, ReducerStrategy*, std::hash<int>> _strategies;
    void initStrategies();
    void addStrategy(ASTNodeType astNodeType, ReducerStrategy* reducerStrategy);
    ASTNode* generateASTNode(ASTNodeType targetAstNodeType, std::vector<ASTNode*> nodes);
public:
    Reducer(TypeSignatureGenerator* typeSignatureGenerator);
    ASTNode* reduce(Handle handle, RecognizerResult* recognizerResult);
};
#endif //JETLANG_REDUCER_H
