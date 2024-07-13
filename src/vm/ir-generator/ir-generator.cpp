//
// Created by Johny Georges on 2024-06-11.
//

#include "ir-generator.h"
#include "ir-strategies/literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/literal-expression-ir-strategy/literal-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/tuple-expression-ir-strategy/tuple-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "ir-strategies/variable-declaration-ir-strategy/variable-declaration-ir-strategy.h"
#include "ir-strategies/function-declaration-ir-strategy/function-declaration-ir-strategy.h"
#include "ir-strategies/function-parameter-list-ir-strategy/function-parameter-list-ir-strategy.h"
#include "ir-strategies/function-return-expression-ir-strategy/function-return-expression-ir-strategy.h"
#include "ir-strategies/procedure-declaration-ir-strategy/procedure-declaration-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/literal-type-signature-ir-strategy/literal-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/class-type-signature-ir-strategy/class-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/enum-type-signature-ir-strategy/enum-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/function-type-signature-ir-strategy/function-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/lambda-type-signature-ir-strategy/lambda-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/invocable-type-signature-ir-strategies/procedure-type-signature-ir-strategy/procedure-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-list-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/struct-type-signature-ir-strategy/struct-type-signature-ir-strategy.h"
#include "ir-strategies/type-signature-ir-strategies/tuple-type-signature-ir-strategy/tuple-type-signature-ir-strategy.h"
#include "../../core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"
#include "../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../shared/utils/logger/logger.h"


// The IRGenerator will be responsible for programmatically generating
// vm code.
// we need to figure out how to generate vm code for an ASTNode and its
// type signature.
IRGenerator::IRGenerator() {
    _context = std::make_unique<llvm::LLVMContext>();
    _irStrategyMap = IRStrategyMap();
}

IRNode* IRGenerator::generateFor(ASTNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    if (ASTNodeUtils::isDeclarationNode(node)) {
        return this->generateFor(((ASTDeclarationNode*)node), scope, irModuleNode);
    } else if (ASTNodeUtils::isStatementNode(node)) {
        return this->generateFor(((ASTStatementNode*)node), scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for node " + node->toString());
}

IRStatementNode* IRGenerator::generateFor(ASTStatementNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    if (node->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getFunctionReturnExpressionIRStrategy()->generate((ASTFunctionReturnExpressionNode*)node, &_context, this, scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for statement " + node->toString());
}

IRDeclarationNode* IRGenerator::generateFor(ASTDeclarationNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getVariableDeclarationIRStrategy()->generate((ASTVariableDeclarationNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_FUNCTION_DECLARATION_NODE)) {
        return this->_irStrategyMap.getFunctionDeclarationIRStrategy()->generate((ASTFunctionDeclarationNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_PROCEDURE_DECLARATION_NODE)) {
        return this->_irStrategyMap.getProcedureDeclarationIRStrategy()->generate((ASTProcedureDeclarationNode*)node, &_context, this, scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for declaration " + node->toString());
}

IRFunctionParameterListNode* IRGenerator::generateFor(ASTFunctionParameterListNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode, llvm::Function* irFunction) {
    return this->_irStrategyMap.getFunctionParameterListIRStrategy()->generate(node, &_context, this, scope, irModuleNode, irFunction);
}

IRExpressionNode* IRGenerator::generateFor(ASTExpressionNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    if (node->is(AST_LITERAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLiteralExpressionIRStrategy()->generate((ASTLiteralExpressionNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_BINARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate((ASTBinaryExpressionNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_LOGICAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLogicalExpressionIRStrategy()->generate((ASTLogicalExpressionNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_ARRAY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayExpressionIRStrategy()->generate((ASTArrayExpressionNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getArrayAccessExpressionIRStrategy()->generate((ASTArrayAccessExpressionNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_STRUCT_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getStructExpressionIRStrategy()->generate((ASTStructExpressionNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_UNARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getUnaryExpressionIRStrategy()->generate((ASTUnaryExpressionNode*)node, &_context, this, scope, irModuleNode);
    } else if (node->is(AST_TUPLE_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getTupleExpressionIRStrategy()->generate((ASTTupleExpressionNode *) node, &_context,this, scope, irModuleNode);
    } else if (node->is(AST_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getIdentifierExpressionIRStrategy()->generate((ASTIdentifierExpressionNode*)node, &_context, scope, irModuleNode);
    }
    throw std::logic_error("unable to generate llvm value for expression " + node->toString());
}

IRLiteralNode* IRGenerator::generateFor(ASTLiteralNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode) {
    switch (node->getNodeType()) {
        case AST_INT_LITERAL_NODE:
            return _irStrategyMap.getIntLiteralIRStrategy()->generate((ASTIntLiteralNode*)node, &_context);;
        case AST_FLOAT_LITERAL_NODE:
            return _irStrategyMap.getFloatLiteralIRStrategy()->generate((ASTFloatLiteralNode*)node, &_context);
        case AST_CHAR_LITERAL_NODE:
            return _irStrategyMap.getCharLiteralIRStrategy()->generate((ASTCharLiteralNode*)node, &_context);
        case AST_STRING_LITERAL_NODE:
            return _irStrategyMap.getStringLiteralIRStrategy()->generate((ASTStringLiteralNode*)node, &_context);
        case AST_BOOLEAN_LITERAL_NODE:
            return _irStrategyMap.getBoolLiteralIRStrategy()->generate((ASTBooleanLiteralNode*)node, &_context);
        default:
            throw std::logic_error("unknown literal node");
    }
}

IRType* IRGenerator::generateTypeFor(TypeSignature* typeSignature) {
    switch (typeSignature->getTypeSource()) {
        case VOID_TYPE_SOURCE:
            return this->generateVoidType();
        case ARRAY_TYPE_SOURCE:
            return _irStrategyMap.getArrayTypeSignatureIRStrategy()->generate((ArrayTypeSignature*)typeSignature, &_context, this);
        case CLASS_TYPE_SOURCE:
            return _irStrategyMap.getClassTypeSignatureIRStrategy()->generate((ClassTypeSignature*)typeSignature, &_context, this);
        case ENUM_TYPE_SOURCE:
            return _irStrategyMap.getEnumTypeSignatureIRStrategy()->generate((EnumTypeSignature*)typeSignature, &_context, this);
        case FUNCTION_TYPE_SOURCE:
            return _irStrategyMap.getFunctionTypeSignatureIRStrategy()->generate((FunctionTypeSignature*)typeSignature, &_context, this);
        case PROCEDURE_TYPE_SOURCE:
            return _irStrategyMap.getProcedureTypeSignatureIRStrategy()->generate((ProcedureTypeSignature*)typeSignature, &_context, this);
        case LAMBDA_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate((LambdaExpressionTypeSignature*)typeSignature, &_context, this);
        case FUNCTION_LAMBDA_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate((FunctionLambdaTypeSignature*)typeSignature, &_context, this);
        case PROCEDURE_LAMBDA_TYPE_SOURCE:
            return _irStrategyMap.getLambdaTypeSignatureIRStrategy()->generate((ProcedureLambdaTypeSignature*)typeSignature, &_context, this);
        case STRUCT_TYPE_SOURCE:
            return _irStrategyMap.getStructTypeSignatureIRStrategy()->generate((StructTypeSignature*)typeSignature, &_context, this);
        case TUPLE_TYPE_SOURCE:
            return _irStrategyMap.getTupleTypeSignatureIRStrategy()->generate((TupleTypeSignature*)typeSignature, &_context, this);
        case INT_LITERAL_TYPE_SOURCE:
        case FLOAT_LITERAL_TYPE_SOURCE:
        case CHAR_LITERAL_TYPE_SOURCE:
        case STRING_LITERAL_TYPE_SOURCE:
        case BOOL_LITERAL_TYPE_SOURCE:
            return _irStrategyMap.getLiteralTypeSignatureIRStrategy()->generate((LiteralTypeSignature*)typeSignature, &_context);
        default:
            throw std::logic_error("unable to generate llvm type for type-signature " + typeSignature->toString());
    }
}

IRType* IRGenerator::generateVoidType() {
    return new IRType(llvm::Type::getVoidTy(*_context));
}

IRParameterListType* IRGenerator::generateParameterList(ParameterListTypeSignature* parameterList) {
    return _irStrategyMap.getParameterListTypeSignatureIRStrategy()->generate(parameterList, &_context, this);
}

IRParameterType* IRGenerator::generateParameterType(ParameterListItemTypeSignature* parameter) {
    return _irStrategyMap.getParameterTypeSignatureIRStrategy()->generate(parameter, &_context, this);
}

llvm::Type* IRGenerator::determineBestFitType(std::vector<llvm::Value*> elementValues) {

    auto largestType = new IRType(elementValues[0]->getType());
    for (auto element : elementValues) {
        auto elementType = new IRType(element->getType());
        if (elementType->isGreaterThan(largestType)) {
            largestType = elementType;
        }
    }
    return largestType->getType();
}

llvm::Constant* IRGenerator::generateZeroConstant() {
    return llvm::ConstantInt::get(*_context, llvm::APInt(32, 0));
}

IRBlockNode* IRGenerator::generateBasicBlock() {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context));
}

IRBlockNode* IRGenerator::generateFunctionBlock(llvm::Function* irFunction) {
    return new IRBlockNode(llvm::BasicBlock::Create(*_context, "entry", irFunction));
}

IRModuleNode* IRGenerator::generateModule(std::string moduleName) {
    return new IRModuleNode(new llvm::Module(moduleName, *_context));
}

IRFunctionNode* IRGenerator::generateEmptyFunction(std::string functionName, IRModuleNode* irModuleNode) {
    auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(*_context), {});
    return new IRFunctionNode(
        llvm::Function::Create(functionType, llvm::GlobalValue::PrivateLinkage, functionName, irModuleNode->getModule())
    );
}