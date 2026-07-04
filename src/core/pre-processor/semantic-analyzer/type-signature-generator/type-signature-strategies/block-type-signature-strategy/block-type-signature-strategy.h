//
// Created by Johny Georges on 2024-05-23.
//

#ifndef JETLANG_BLOCK_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_BLOCK_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../type-signature/type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-finally-block-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-try-block-node.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-block-node.h"

class BlockTypeSignatureStrategy {
private:
    void assignContents(std::vector<std::shared_ptr<ASTNode>>* content, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
public:
    void assign(std::shared_ptr<ASTBlockNode> blockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assign(std::shared_ptr<ASTControlFlowBlockNode> controlFlowBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assign(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assign(std::shared_ptr<ASTTryBlockNode> tryBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assign(std::shared_ptr<ASTCatchBlockNode> catchBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assign(std::shared_ptr<ASTFinallyBlockNode> finallyBlockNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};


#endif //JETLANG_BLOCK_TYPE_SIGNATURE_STRATEGY_H
