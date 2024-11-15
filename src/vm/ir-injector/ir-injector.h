//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_IR_INJECTOR_H
#define JETLANG_IR_INJECTOR_H

#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-block-node.h"
#include "./ir-injector-map.h"

class IRInjector {
private:
    IRInjectorMap _irInjectorMap;
public:
    IRInjector();
    void inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, IRModuleNode* irModule);
    void inject(IRBlockNode* irBlock, IRStatementNode* irStatement, IRModuleNode* irModule);
    llvm::Value* inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperationType irOperationType, IRModuleNode* irModule);
    llvm::Value* injectRawString(IRBlockNode* irBlock, std::string rawString, IRArrayPointerType* stringPointerType, IRModuleNode* irModule);
};

#endif //JETLANG_IR_INJECTOR_H
