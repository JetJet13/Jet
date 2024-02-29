//
// Created by Johny Georges on 2024-02-08.
//

#include "reducer.h"
#include "reducer-strategies/variable-init-reducer-strategy/variable-init-reducer-strategy.h"
#include "reducer-strategies/variable-declaration-reducer-strategy/variable-declaration-reducer-strategy.h"
#include "reducer-strategies/unary-expression-reducer-strategy/unary-expression-reducer-strategy.h"
#include "reducer-strategies/binary-expression-reducer-strategy/binary-expression-reducer-strategy.h"
#include "reducer-strategies/logical-expression-reducer-strategy/logical-expression-reducer-strategy.h"
#include "reducer-strategies/identifier-expression-reducer-strategy/identifier-expression-reducer-strategy.h"
#include "reducer-strategies/literal-expression-reducer-strategy/literal-expression-reducer-strategy.h"

Reducer::Reducer() {
    _strategies = std::unordered_map<ASTNodeType, ReducerStrategy*, std::hash<int>>();
    this->initStrategies();
}

void Reducer::initStrategies() {
    this->addStrategy(AST_VARIABLE_INIT_NODE, new VariableInitReducerStrategy());
    this->addStrategy(AST_VARIABLE_DECLARATION_NODE, new VariableDeclarationReducerStrategy());
    this->addStrategy(AST_UNARY_EXPRESSION_NODE, new UnaryExpressionReducerStrategy());
    this->addStrategy(AST_BINARY_EXPRESSION_NODE, new BinaryExpressionReducerStrategy());
    this->addStrategy(AST_LOGICAL_EXPRESSION_NODE, new LogicalExpressionReducerStrategy());
    this->addStrategy(AST_IDENTIFIER_EXPRESSION_NODE, new IdentifierExpressionReducerStrategy());
    this->addStrategy(AST_LITERAL_EXPRESSION_NODE, new LiteralExpressionReducerStrategy());
//    this->addStrategy(AST_PLUS_OPERATOR_NODE, new BinaryOperatorReducerStrategy());
//    this->addStrategy(AST_MINUS_OPERATOR_NODE, new BinaryOperatorReducerStrategy());
//    this->addStrategy(AST_STAR_OPERATOR_NODE, new BinaryOperatorReducerStrategy());
//    this->addStrategy(AST_SLASH_OPERATOR_NODE, new BinaryOperatorReducerStrategy());
//    this->addStrategy(AST_MODULO_OPERATOR_NODE, new BinaryOperatorReducerStrategy());
}

void Reducer::addStrategy(ASTNodeType astNodeType, ReducerStrategy* reducerStrategy) {
    _strategies.insert(std::pair<ASTNodeType, ReducerStrategy*>(astNodeType, reducerStrategy));
}


ASTNode* Reducer::reduce(Handle handle, RecognizerResult* recognizerResult) {
    if (handle.isEmpty()) {
        throw std::invalid_argument("handle cannot be empty");
    }

    if (recognizerResult->getNumReducedNodes() == 1 && handle.isNodeTypeAt(0, recognizerResult->getTargetAstNodeType())) {
        return handle.at(0).value();
    }

    auto nodesToReduce = handle.getFirstNodes(recognizerResult->getNumReducedNodes());

    return this->generateASTNode(recognizerResult->getTargetAstNodeType(), nodesToReduce);
}

ASTNode* Reducer::generateASTNode(ASTNodeType targetAstNodeType, std::vector<ASTNode*> nodes) {
    auto reducerStrategy = _strategies.find(targetAstNodeType);
    if (reducerStrategy == _strategies.end()) {
        throw std::invalid_argument("unable to determine reduced AST Node Type for given list of nodes");
    }
    return reducerStrategy->second->execute(nodes);
}
