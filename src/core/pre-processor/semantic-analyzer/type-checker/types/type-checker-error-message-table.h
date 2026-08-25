//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
#define JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H

#include <functional>

using ErrorMessageLambda = std::function<std::shared_ptr<TypeCheckError>()>;

namespace TypeCheckerErrorMessageTable {
    static std::shared_ptr<TypeCheckError> generateMessage(std::shared_ptr<ASTNode> node, std::string message) {
        auto typeCheckMessage = "(" + node->getLineColumn() + ") - " + message + "\n" + node->toSourceCode() + "\n";
        return std::make_shared<TypeCheckError>(typeCheckMessage, node->getFilePath());
    }
    static ErrorMessageLambda GlobalVariableNameConflictsWithBuiltInFunctionName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "global variable name conflicts with built-in function"); };
    }
    static ErrorMessageLambda FunctionNameConflictsWithBuiltInFunctionName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "function name conflicts with built-in function"); };
    }
    static ErrorMessageLambda ProcedureNameConflictsWithBuiltInFunctionName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "procedure name conflicts with built-in function"); };
    }
    static ErrorMessageLambda FunctionTypeSignatureConflictsWithAnotherFunction(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "function type signature conflicts with another function"); };
    }
    static ErrorMessageLambda ProcedureTypeSignatureConflictsWithAnotherProcedure(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "procedure type signature conflicts with another procedure"); };
    }
    static ErrorMessageLambda ClassNameConflictsWithAnotherClass(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class name conflicts with another class declaration"); };
    }
    static ErrorMessageLambda EnumNameConflictsWithAnotherEnum(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "enum name conflicts with another enum declaration"); };
    }
    static ErrorMessageLambda CustomTypeNameConflictsWithAnotherCustomType(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "type name conflicts with another type declaration"); };
    }
    static ErrorMessageLambda VariableTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type does not match initializer type"); };
    } 
    static ErrorMessageLambda VariableTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type is unknown");  };
    } 
    static ErrorMessageLambda VariableTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type is invalid");  };
    } 
    static ErrorMessageLambda VariableTypeVoid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type cannot be void");  };
    }
    static ErrorMessageLambda VariableAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type does not match expression type");  };
    }
    static ErrorMessageLambda VariableAssignmentNotAllowed(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable cannot be re-assigned because it was declared as a constant");  };
    }
    static ErrorMessageLambda ModuleAccessAssignmentNotAllowed(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "module variable cannot be re-assigned because it was declared as a constant");  };
    }
    static ErrorMessageLambda ClassPropertyAssignmentNotAllowed(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property cannot be re-assigned because it was declared as a constant");  };
    }
    static ErrorMessageLambda PrivateClassPropertyAssignmentNotAllowed(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property cannot be re-assigned outside of its class because it is private");  };
    }
    static ErrorMessageLambda ClassPropertyIsPrivate(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property cannot be accessed outside of its class because it is private");  };
    }
    static ErrorMessageLambda SharedValueAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable ref value type does not match expression type"); };
    }
    static ErrorMessageLambda SharedValueAssignmentTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable type is not ref type"); };
    }
    static ErrorMessageLambda ArrayAccessSharedValueAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type does not match expression type. Expected ref type"); };
    }
    static ErrorMessageLambda ArrayAccessSharedValueAssignmentTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type is not ref type"); };
    }
    static ErrorMessageLambda ObjectAccessSharedValueAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "property type does not match expression type. Expected ref type"); };
    }
    static ErrorMessageLambda ObjectAccessSharedValueAssignmentTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "property type is not ref type"); };
    }
    static ErrorMessageLambda TupleAccessSharedValueAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "tuple property type does not match expression type. Expected ref type"); };
    }
    static ErrorMessageLambda TupleAccessSharedValueAssignmentTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "tuple property type is not ref type"); };
    }
    static ErrorMessageLambda ModuleAccessSharedValueAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "module export type does not match expression type. Expected ref type"); };
    }
    static ErrorMessageLambda ModuleAccessSharedValueAssignmentTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "module export type is not ref type"); };
    }
    static ErrorMessageLambda ProcedureHasReturnExpression(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "procedure cannot have a return statement");  };
    } 
    static ErrorMessageLambda ParameterTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "parameter type is unknown"); };
    } 
    static ErrorMessageLambda ParameterTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "parameter type is invalid"); };
    } 
    static ErrorMessageLambda ParameterTypeVoid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "parameter type cannot be void"); };
    } 
    static ErrorMessageLambda FunctionReturnTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "function return type is unknown"); };
    } 
    static ErrorMessageLambda FunctionReturnTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "function return type is invalid"); };
    } 
    static ErrorMessageLambda FunctionReturnTypeVoid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "function return type cannot be void. Create a procedure instead."); };
    } 
    static ErrorMessageLambda FunctionNotAllPathsReturn(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not all function paths return a value"); };
    } 
    static ErrorMessageLambda FunctionReturnExpressionMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "return expression type does not match function return type"); };
    } 
    static ErrorMessageLambda ExpressionTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "expression type is unknown"); };
    } 
    static ErrorMessageLambda ExpressionTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "expression type is invalid"); };
    } 
    static ErrorMessageLambda ExpressionTypeVoid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "expression type cannot be void"); };
    } 
    static ErrorMessageLambda EnumKeyValueTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "enum key-value type does not match enum type"); };
    } 
    static ErrorMessageLambda ControlFlowConditionNotBool(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "condition must evaluate to true or false"); };
    } 
    static ErrorMessageLambda ForInStatementSourceNotIterable(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "source of for-in loop is not iterable"); };
    }
    static ErrorMessageLambda NotInvocable(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not invocable"); };
    }
    static ErrorMessageLambda ClassPropertyTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type is unknown"); };
    } 
    static ErrorMessageLambda ClassPropertyTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type is invalid"); };
    } 
    static ErrorMessageLambda ClassPropertyTypeVoid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type cannot be void"); };
    } 
    static ErrorMessageLambda ClassPropertyAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type does not match expression type"); };
    }
    static ErrorMessageLambda ClassPropertySharedValueAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property ref value type does not match expression type"); };
    }
    static ErrorMessageLambda ClassPropertySharedValueAssignmentTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property type is not ref type"); };
    }
    static ErrorMessageLambda ClassPropertyInitializerTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "type of initial value for class property does not match class property type"); };
    }
    static ErrorMessageLambda ClassPropertySelfReference(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class self-referencing is not supported"); };
    }
    static ErrorMessageLambda ClassPropertyCircularReference(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class circular references are not supported"); };
    }
    static ErrorMessageLambda ClassPropertyInvocable(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property cannot be invocable. Only class methods can be invocable"); };
    }
    static ErrorMessageLambda ClassPropertyNamesNotUnique(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property names must be unique"); };
    }
    static ErrorMessageLambda ClassPropertyNameConflictsWithMethodName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property names must not conflict with method names"); };
    }
    static ErrorMessageLambda ClassPropertyNameConflictsWithStaticPropertyName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property names must not conflict with static property names"); };
    }
    static ErrorMessageLambda ClassPropertyNameConflictsWithStaticMethodName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class property names must not conflict with static method names"); };
    }
    static ErrorMessageLambda ClassMethodNameConflictsWithStaticPropertyName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class method names must not conflict with static property names"); };
    }
    static ErrorMessageLambda ClassMethodNameConflictsWithStaticMethodName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class method names must not conflict with static method names"); };
    }
    static ErrorMessageLambda ClassStaticPropertyNameConflictsWithStaticMethodName(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class static property names must not conflict with static method names"); };
    }
    static ErrorMessageLambda ClassMethodNamesAndTypeSignaturesNotUnique(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "one or more class methods have the same name and type-signature"); };
    } 
    static ErrorMessageLambda ClassConstructorsNotUnique(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class constructors must have unique parameter lists"); };
    }
    static ErrorMessageLambda ClassConstructorHasReturnExpression(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class constructor cannot have a return statement"); };
    }
    static ErrorMessageLambda ClassMethodReturnTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class method return type is unknown"); };
    } 
    static ErrorMessageLambda ClassMethodReturnTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class method return type is invalid"); };
    } 
    static ErrorMessageLambda ClassMethodReturnTypeVoid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class method return type cannot be void"); };
    } 
    static ErrorMessageLambda ClassMethodNotAllPathsReturn(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not all class method paths return a value"); };
    }
    static ErrorMessageLambda ClassMethodHasReturnExpression(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class method cannot have a return statement because it has no return type"); };
    }
    static ErrorMessageLambda ClassDoesNotImplementInterface(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "class does not satisfy interface it declared to implement"); };
    }
    static ErrorMessageLambda ArrayElementTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not all array elements match the array element type"); };
    } 
    static ErrorMessageLambda ClassMethodCallNotEnoughArguments(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not enough arguments provided for class method call"); };
    } 
    static ErrorMessageLambda ClassMethodCallTooManyArguments(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "too many arguments provided for class method call"); };
    } 
    static ErrorMessageLambda ClassMethodCallArgumentTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "argument type does not match parameter type for class method call"); };
    } 
    static ErrorMessageLambda NotCallableCurryType(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "curry function type is not callable"); };
    } 
    static ErrorMessageLambda CurryCallNotEnoughArguments(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not enough arguments provided for curry call"); };
    } 
    static ErrorMessageLambda CurryCallTooManyArguments(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "too many arguments provided for curry call"); };
    } 
    static ErrorMessageLambda CurryCallArgumentTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "argument type does not match parameter type for curry call"); };
    } 
    static ErrorMessageLambda FunctionCallNotEnoughArguments(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not enough arguments provided for function call"); };
    } 
    static ErrorMessageLambda FunctionCallTooManyArguments(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "too many arguments provided for function call"); };
    } 
    static ErrorMessageLambda FunctionCallArgumentTypeMismatch(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "argument type does not match parameter type for function call"); };
    } 
    static ErrorMessageLambda LambdaExpressionReturnTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "lambda expression return type is unknown"); };
    } 
    static ErrorMessageLambda LambdaExpressionReturnTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "lambda expression return type is invalid"); };
    } 
    static ErrorMessageLambda LambdaExpressionNotAllPathsReturn(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "not all lambda expression paths return a value"); };
    }
    static ErrorMessageLambda LambdaExpressionHasReturnExpression(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "lambda expression cannot have a return statement"); };
    }
    static ErrorMessageLambda NewClassInstanceNotClassType(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "cannot instantiate new class instance since type is not a class type"); };
    }
    static ErrorMessageLambda NewClassInstanceNoMatchingConstructor(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "cannot instantiate new class instance since no constructor found for arguments provided"); };
    }
    static ErrorMessageLambda VariableNamesNotUnique(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "variable name must be unique"); };
    }
    static ErrorMessageLambda InvalidSingleImportModuleName(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "imported module name is invalid"); };
    }
    static ErrorMessageLambda DrefExpressionTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "dref expression does not have type ref"); };
    }
    static ErrorMessageLambda RefExpressionTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "ref expression cannot have type ref"); };
    }
    static ErrorMessageLambda ShareExpressionTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "share expression cannot have type shared"); };
    }
    static ErrorMessageLambda InterfacePropertyTypeUnknown(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property type is unknown"); };
    }
    static ErrorMessageLambda InterfacePropertyTypeInvalid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property type is invalid"); };
    }
    static ErrorMessageLambda InterfacePropertyTypeVoid(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property type cannot be void"); };
    }
    static ErrorMessageLambda InterfacePropertyNamesNotUnique(std::shared_ptr<ASTNode> node) {
      return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "interface property names must be unique"); };
    }
    static ErrorMessageLambda ObjectAccessAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type does not match expression type"); };
    }
    static ErrorMessageLambda ModuleAccessAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "imported module variable type does not match expression type"); };
    }
    static ErrorMessageLambda TupleAccessAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "tuple property type does not match expression type"); };
    }
    static ErrorMessageLambda ObjectPropertyTypeUnknown(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type is unknown");  };
    }
    static ErrorMessageLambda ObjectPropertyTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type is invalid");  };
    }
    static ErrorMessageLambda ObjectPropertyTypeVoid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "object property type cannot be void");  };
    }
    static ErrorMessageLambda ArrayAccessAssignmentTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type does not match expression type"); };
    }
    static ErrorMessageLambda ArrayElementTypeUnknown(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type is unknown");  };
    }
    static ErrorMessageLambda ArrayElementTypeInvalid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type is invalid");  };
    }
    static ErrorMessageLambda ArrayElementTypeVoid(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "array element type cannot be void");  };
    }
    static ErrorMessageLambda BinaryExpressionOperandsTypeMismatch(std::shared_ptr<ASTNode> node) {
        return [node]() -> std::shared_ptr<TypeCheckError> { return TypeCheckerErrorMessageTable::generateMessage(node, "binary expression operand types (left, right) are not equivalent"); };
    }
}

#endif //JETLANG_TYPE_CHECKER_ERROR_MESSAGE_TABLE_H
