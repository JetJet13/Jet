//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TYPE_SIGNATURE_H
#define JETLANG_TYPE_SIGNATURE_H

#include <vector>
#include <optional>
#include <string>
#include "types/type-source.h"
#include "types/built-in-type-source.h"
#include "types/built-in-debug-type-source.h"

class TypeSignature : public std::enable_shared_from_this<TypeSignature> {
protected:
    std::string _moduleId;
    std::string _id;
    std::string _keyId;
    std::optional<BuiltInTypeSource> _builtInTypeSource = std::nullopt;
    bool _isDebug = false;
    bool _isPrototype = false;
    bool _isGeneric = false;
public:
    std::string getModuleId();
    std::string getId();
    std::string getKeyId();
    std::shared_ptr<TypeSignature> markAsBuiltIn(BuiltInTypeSource builtInTypeSource);
    std::shared_ptr<TypeSignature> markAsDebug();
    std::shared_ptr<TypeSignature> markAsGeneric();
    bool isBuiltIn();
    bool isDebug();
    bool isGeneric();
    bool isOneOfBuiltInTypeSources(std::vector<BuiltInTypeSource> builtInTypeSources);
    std::shared_ptr<TypeSignature> markAsPrototype();
    bool isPrototype();
    std::shared_ptr<TypeSignature> setModuleId(std::string id);
    std::shared_ptr<TypeSignature> setId(std::string id);
    virtual std::shared_ptr<TypeSignature> setKeyId(std::string id);
    bool typeTargetIs(TypeSource other);
    bool typeSourceIs(TypeSource other);
    bool isOneOf(std::vector<TypeSource> typeSources);
    virtual bool isUnknown();
    virtual bool isInvalid();
    virtual bool isVoid();
    bool isUnknownOrInvalidOrVoid();
    virtual bool isLiteral();
    virtual bool isInvocable();
    virtual void copyFrom(std::shared_ptr<TypeSignature> otherType);
    virtual TypeSource getTypeTarget();
    virtual std::shared_ptr<TypeSignature> getTargetTypeSignature();
    virtual bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType);
    virtual std::shared_ptr<TypeSignature> convertToVariableTypeSignature();
    virtual std::string toDetailString() = 0;
    virtual std::string toString() = 0;
    virtual TypeSource getTypeSource() = 0;
    virtual bool isEqualTo(std::shared_ptr<TypeSignature> otherType) = 0;
    virtual void print() = 0;
};

#endif //JETLANG_TYPE_SIGNATURE_H
