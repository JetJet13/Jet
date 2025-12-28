//
// Created by Johny Georges on 2024-12-05.
//

#ifndef JETLANG_IR_CLASS_TYPE_H
#define JETLANG_IR_CLASS_TYPE_H

#include "ir-struct-type.h"
#include "ir-function-type.h"
#include "ir-parameter-type.h"

class IRClassType : public IRType {
private:
    IRStructType* _classProperties;
    std::optional<IRParameterType*> _classScopeType;
    std::unordered_map<std::string, IRFunctionType*> _classConstructors;
    std::unordered_map<std::string, IRFunctionType*> _classMethods;
    std::string _preConstructorName;
    std::string _name;
public:
    IRClassType(std::string name, IRStructType* classProperties, std::string preConstructorName = "");
    IRClassType(std::string name, IRStructType* classProperties, std::optional<IRParameterType*> classScopeType, std::unordered_map<std::string, IRFunctionType*> classConstructors, std::unordered_map<std::string, IRFunctionType*> classMethods, std::string preConstructorName = "");
    std::optional<IRParameterType*> getClassScopeParameterType();
    std::optional<IRFunctionType*> getIRTypeForConstructor(std::string constructorId);
    std::optional<IRFunctionType*> getIRTypeForMethod(std::string methodName);
    llvm::Type* getValueType();
    IRStructType* getClassProperties();
    std::string getPreConstructorName();
    std::string getName();
    void setProperties(IRStructType* classProperties);
    void setClassScopeType(std::optional<IRParameterType*> classScopeType);
    void addMethod(std::string methodName, IRFunctionType* irType);
    void addConstructor(std::string constructorName, IRFunctionType* irType);
    llvm::Type* getType() override;
    bool isClassType() override;
    bool containsTypeThatRequiresFreeing() override;
    llvm::Align getAlignment() override;
    IRClassType* clone() override;
    void print() override;
};

#endif //JETLANG_IR_CLASS_TYPE_H
