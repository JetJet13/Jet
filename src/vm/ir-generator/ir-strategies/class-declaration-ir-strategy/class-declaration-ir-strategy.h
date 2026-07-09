//
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
#define JETLANG_CLASS_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-class-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

class ClassDeclarationIRStrategy {
private:
    std::optional<std::shared_ptr<IRClassPreConstructorNode>> generatePreConstructor(std::shared_ptr<ASTClassDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassConstructorNode> generate(std::shared_ptr<ASTClassConstructorDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassMethodNode> generate(std::shared_ptr<ASTClassMethodDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassMethodNode> generateStatic(std::shared_ptr<ASTClassMethodDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    std::shared_ptr<IRClassStaticPropertyNode> generateStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareStaticMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareConstructor(std::shared_ptr<ASTClassConstructorDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
    void declareStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node, bool isExportable, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IRClassType> irClassType);
public:
    std::shared_ptr<IRClassDeclarationNode> generate(std::shared_ptr<ASTClassDeclarationNode> node,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};


#endif //JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
