//
// Created by Johny Georges on 2024-06-11.
//

#ifndef JETLANG_IR_GENERATOR_H
#define JETLANG_IR_GENERATOR_H

#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "ir-lookup-table/ir-lookup-table.h"
#include "../ast/ast-nodes/ast-declaration-nodes/ast-declaration-node.h"
#include "../ast/ast-nodes/ast-literal-nodes/ast-literal-node.h"

class IRGenerator {
private:
    std::unique_ptr<llvm::LLVMContext> _context;
    std::unique_ptr<llvm::Module> _module;
    std::unique_ptr<llvm::IRBuilder<>> _builder;
    TokenTable* _tokenTable;
public:
    IRGenerator(TokenTable* tokenTable);
    llvm::Value* generateFor(ASTLiteralNode* node, IRLookupTable* scope);
};

#endif //JETLANG_IR_GENERATOR_H
