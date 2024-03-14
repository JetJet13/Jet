//
// Created by Johny Georges on 2024-02-14.
//

#include "syntax-dfa.h"
#include "../../../dfa/dfa-node-factory.h"
#include "../../../dfa/dfa-transition-factory.h"
#include "../../../../shared/utils/logger/logger.h"

SyntaxDfa::SyntaxDfa() {
    _dfa = new DFA();
    this->init();
}

RecognizerResult* SyntaxDfa::recognize(Handle handle) {
    if (handle.isTerminatorOnlyNode() || handle.isGroupingOnlyNode() || handle.isArrayOnlyNode() || handle.isBraceOnlyNode()) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    } else if (handle.isEmpty()) {
        return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
    } else if (!handle.isInSpecialMode()) {
        auto startNode = _dfa->findStartNode(handle.first().value()->getNodeType());
        if (startNode && startNode.value()->alwaysReduceSelf()) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, handle.first().value()->getNodeType());
        }

        auto successor = handle.getNextNodeFor(0);
        if (startNode && successor && startNode.value()->shouldReduceSelfFor(successor.value()->getNodeType())) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, handle.first().value()->getNodeType());
        }
    } else if (handle.isArrayEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle.size(), AST_ARRAY_NODE);
    } else if (handle.isBraceEnclosed()) {
        return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, handle.size(), AST_BLOCK_NODE);
    } else if (handle.isInSpecialMode()) {
        auto predecessor = handle.getPrevNodeFor(0);
        auto successor = handle.getNextNodeFor(0);
        if (predecessor && successor && predecessor.value()->isSameNodeTypeAs(successor.value()) && predecessor.value()->isHigherPriorityThan(successor.value())) {
            Logger::log("predecessor is higher priority then successor");
            return new RecognizerResult(RECOGNIZER_ACTION_POP);
        }
        auto startNode = _dfa->findStartNode(handle.first().value()->getNodeType());
        if (startNode && predecessor && startNode.value()->shouldReduceToTargetFor(predecessor.value()->getNodeType())) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, 1, startNode.value()->getReduceTargetFor(predecessor.value()->getNodeType()).value());
        }
    }

    auto startNode = _dfa->findStartNode(handle.first().value()->getNodeType());
    auto predecessor = handle.getPrevNodeFor(0);
    if (startNode && predecessor && startNode.value()->shouldBacktrackTo(predecessor.value()->getNodeType())) {
        return new RecognizerResult(RECOGNIZER_ACTION_POP);
    }
    for (int i = 0; i < handle.size(); i++) {
        auto nodeType = handle.at(i).value()->getNodeType();
        if (i == 0) {
            _dfa->init(nodeType);
        } else {
            _dfa->determine(nodeType);
        }

        auto currentDfaState = _dfa->getCurrentState();
        if (currentDfaState && currentDfaState.value()->hasTargetAstNodeType()) {
            return new RecognizerResult(RECOGNIZER_ACTION_REDUCE, i + 1, currentDfaState.value()->getTargetAstNodeType().value());
        } else if (handle.isInSpecialMode() && !currentDfaState) {
            return new RecognizerResult(RECOGNIZER_ACTION_POP);
        } else if (!currentDfaState) {
            return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
        }
    }

    return new RecognizerResult(RECOGNIZER_ACTION_SHIFT);
}

DFA* SyntaxDfa::getDFA() {
    return _dfa;
}

void SyntaxDfa::init() {

    DFANode* varDeclaration = DFANodeFactory::Once::createWithTarget(AST_VARIABLE_DECLARATION_NODE, AST_VARIABLE_DECLARATION_NODE);
    DFANode* varInit = DFANodeFactory::Once::create(AST_VARIABLE_INIT_NODE);
    DFANode* varType = DFANodeFactory::Once::create(AST_VARIABLE_TYPE_NODE);
    DFANode* identifierExpression = DFANodeFactory::Once::create(AST_IDENTIFIER_EXPRESSION_NODE);
    DFANode* literalExpression = DFANodeFactory::Once::create(AST_LITERAL_EXPRESSION_NODE);
    DFANode* arrayAccessExpression = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_EXPRESSION_NODE);
    DFANode* arrayExpression = DFANodeFactory::Once::create(AST_ARRAY_EXPRESSION_NODE);
    DFANode* structExpression = DFANodeFactory::Once::create(AST_STRUCT_EXPRESSION_NODE);
    DFANode* binaryExpression = DFANodeFactory::Once::create(AST_BINARY_EXPRESSION_NODE);
    DFANode* logicalExpression = DFANodeFactory::Once::create(AST_LOGICAL_EXPRESSION_NODE);
    DFANode* unaryExpression = DFANodeFactory::Once::create(AST_UNARY_EXPRESSION_NODE);
    DFANode* binaryOperator = DFANodeFactory::Once::create(AST_BINARY_OPERATOR_NODE);
    DFANode* logicalOperator = DFANodeFactory::Once::create(AST_LOGICAL_OPERATOR_NODE);
    DFANode* unaryOperator = DFANodeFactory::Once::create(AST_UNARY_OPERATOR_NODE);
    DFANode* arrayBase = DFANodeFactory::Once::create(AST_ARRAY_NODE);
    DFANode* arrayAccess = DFANodeFactory::Once::create(AST_ARRAY_ACCESS_NODE);
    DFANode* structKeyValue = DFANodeFactory::Once::create(AST_STRUCT_KEY_VALUE_NODE);
    DFANode* block = DFANodeFactory::Once::create(AST_BLOCK_NODE);
    DFANode* colon = DFANodeFactory::Once::create(AST_COLON_NODE);



    this->initVarType(varType);
    this->initVarInit(varInit);

    logicalOperator
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_LOGICAL_EXPRESSION_NODE)));

    binaryOperator
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_BINARY_EXPRESSION_NODE)));

    unaryOperator
    ->reduceSelfWhenNextNodeIsOneOf({
            AST_GROUP_START_NODE
    })
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_UNARY_EXPRESSION_NODE)));

    identifierExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
          AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator))
    ->addTransition(DFATransitionFactory::create(colon))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));
    

    literalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
         AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));

    arrayExpression
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));

    arrayAccessExpression
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE)));


    binaryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
        AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));
    

    logicalExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
       AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator));
    

    unaryExpression
    ->backtrackWhenLastReducedNodeIsOneOf({
       AST_UNARY_OPERATOR_NODE
    })
    ->markAlwaysReduceSelf()
    ->addTransition(DFATransitionFactory::create(logicalOperator))
    ->addTransition(DFATransitionFactory::create(binaryOperator));

    arrayBase
    ->addReduceToTargetMap(new ReduceToTargetMap(AST_ARRAY_EXPRESSION_NODE, { AST_VARIABLE_INIT_NODE, AST_COMMA_NODE, AST_LEFT_BRACKET_NODE }))
    ->addReduceToTargetMap(new ReduceToTargetMap(AST_ARRAY_ACCESS_NODE, { AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE, AST_ARRAY_EXPRESSION_NODE, AST_ARRAY_ACCESS_EXPRESSION_NODE }));

    arrayAccess
    ->backtrackWhenLastReducedNodeIsOneOf({ AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE, AST_ARRAY_EXPRESSION_NODE });

    block
    ->markAlwaysReduceSelf()
    ->addReduceToTargetMap(new ReduceToTargetMap(AST_STRUCT_EXPRESSION_NODE, { AST_VARIABLE_INIT_NODE, AST_COLON_NODE  }));

    colon
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_STRUCT_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)))
    ->addTransition(DFATransitionFactory::create(DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_STRUCT_KEY_VALUE_NODE)));

    _dfa
    ->insertStartNode(varDeclaration)
    ->insertStartNode(varType)
    ->insertStartNode(varInit)
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_NODE, AST_IDENTIFIER_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_LITERAL_EXPRESSION_NODE))
    ->insertStartNode(identifierExpression)
    ->insertStartNode(literalExpression)
    ->insertStartNode(structExpression)
    ->insertStartNode(arrayExpression)
    ->insertStartNode(arrayAccessExpression)
    ->insertStartNode(binaryExpression)
    ->insertStartNode(logicalExpression)
    ->insertStartNode(unaryExpression)
    ->insertStartNode(DFANodeFactory::Once::create(AST_GROUP_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_LEFT_BRACKET_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_BLOCK_START_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_COMMA_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(DFANodeFactory::Once::create(AST_COLON_NODE)->markAlwaysReduceSelf())
    ->insertStartNode(unaryOperator)
    ->insertStartNode(arrayBase)
    ->insertStartNode(arrayAccess)
    ->insertStartNode(structKeyValue)
    ->insertStartNode(block)
    ->insertStartNode(DFANodeFactory::Once::create(AST_BINARY_OPERATOR_NODE)
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                          AST_BINARY_EXPRESSION_NODE,
                          AST_UNARY_EXPRESSION_NODE,
                          AST_LITERAL_EXPRESSION_NODE,
                          AST_IDENTIFIER_EXPRESSION_NODE
                      }))
    ->insertStartNode(DFANodeFactory::Once::create(logicalOperator->getNodeType())
                      ->markAlwaysReduceSelf()
                      ->backtrackWhenLastReducedNodeIsOneOf({
                          AST_BINARY_EXPRESSION_NODE,
                          AST_UNARY_EXPRESSION_NODE,
                          AST_LITERAL_EXPRESSION_NODE,
                          AST_IDENTIFIER_EXPRESSION_NODE
                      }));
}

void SyntaxDfa::initVarType(DFANode* varTypeNode) {
    varTypeNode
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::create(AST_IDENTIFIER_NODE)
                    ->addTransition(
                            DFATransitionFactory::create(
                                DFANodeFactory::Once::createWithTarget(AST_ASSIGNMENT_OPERATOR_NODE, AST_VARIABLE_INIT_NODE)))
            )
    );
}

void SyntaxDfa::initVarInit(DFANode* varInitNode) {

    varInitNode
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_LITERAL_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_IDENTIFIER_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_ARRAY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_ARRAY_ACCESS_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_BINARY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_LOGICAL_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_UNARY_EXPRESSION_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_INT_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_FLOAT_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_STRING_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_CHAR_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)))
    ->addTransition(
            DFATransitionFactory::create(
                    DFANodeFactory::Once::createWithTarget(AST_BOOLEAN_LITERAL_NODE, AST_VARIABLE_DECLARATION_NODE)));

}