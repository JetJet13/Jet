//
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_IR_CLASS_TYPE_H
#define JETLANG_IR_CLASS_TYPE_H

#include "ir-struct-ref-type.h"
#include "ir-function-type.h"
#include "ir-parameter-type.h"

class IRClassType : public IRType {
private:
    std::shared_ptr<IRStructRefType> _classProperties;
    std::optional<std::shared_ptr<IRParameterType>> _classScopeType;
    std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> _classConstructors;
    std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> _classMethods;
    std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> _classStaticMethods;
    std::unordered_map<std::string, std::shared_ptr<IRType>> _classStaticProperties;
    std::string _preConstructorName;
    std::string _name;
public:
    IRClassType(std::string name, std::shared_ptr<IRStructRefType> classProperties, std::string preConstructorName = "");
    IRClassType(std::string name, std::shared_ptr<IRStructRefType> classProperties, std::optional<std::shared_ptr<IRParameterType>> classScopeType, std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> classConstructors, std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> classMethods, std::unordered_map<std::string, std::shared_ptr<IRFunctionType>> classStaticMethods, std::unordered_map<std::string, std::shared_ptr<IRType>> classStaticProperties, std::string preConstructorName = "");
    std::optional<std::shared_ptr<IRParameterType>> getClassScopeParameterType();
    std::optional<std::shared_ptr<IRFunctionType>> getIRTypeForConstructor(std::string constructorId);
    std::optional<std::shared_ptr<IRFunctionType>> getIRTypeForMethod(std::string methodName);
    std::optional<std::shared_ptr<IRFunctionType>> getIRTypeForStaticMethod(std::string propertyName);
    std::optional<std::shared_ptr<IRType>> getIRTypeForStaticProperty(std::string propertyName);
    std::string getIRMethodName(std::string methodName);
    std::string getIRStaticMethodName(std::string methodName);
    std::string addStaticSuffix(std::string methodName);
    std::string getIRPropertyName(std::string propertyName);
    llvm::Type* getValueType();
    std::shared_ptr<IRStructRefType> getClassProperties();
    std::string getPreConstructorName();
    std::string getName();
    void setProperties(std::shared_ptr<IRStructRefType> classProperties);
    void setClassScopeType(std::optional<std::shared_ptr<IRParameterType>> classScopeType);
    void addStaticProperty(std::string staticPropertyName, std::shared_ptr<IRType> irType);
    void addMethod(std::string methodName, std::shared_ptr<IRFunctionType> irType);
    void addStaticMethod(std::string methodName, std::shared_ptr<IRFunctionType> irType);
    void addConstructor(std::string constructorName, std::shared_ptr<IRFunctionType> irType);
    llvm::Type* getType() override;
    bool isClassType() override;
    bool containsTypeThatRequiresFreeing() override;
    llvm::Align getAlignment() override;
    std::shared_ptr<IRType> clone() override;
    void print() override;
};

#endif //JETLANG_IR_CLASS_TYPE_H
