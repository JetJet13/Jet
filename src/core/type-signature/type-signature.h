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
// created lambda analyzer in post-processor to mark variables as captured, so we
// store them on the heap (i.e. malloc) but we now need to generate the lambda scope
// parameter using only the variables marked as captured. This isn't possible at the moment
// because we generate the lambda scope parameter before the post-processor runs.

// added captured variables list to ast lambda expression nodes. The only thing left to do is to populate them.

class TypeSignature {
protected:
    std::string _id;
    std::string _keyId;
    std::optional<BuiltInTypeSource> _builtInTypeSource = {};
    bool _isPrototype = false;
public:
    std::string getId();
    std::string getKeyId();
    TypeSignature* markAsBuiltIn(BuiltInTypeSource builtInTypeSource);
    bool isBuiltIn();
    bool builtInTypeSourceIs(BuiltInTypeSource builtInTypeSource);
    bool isOneOfBuiltInTypeSources(std::vector<BuiltInTypeSource> builtInTypeSources);
    TypeSignature* markAsPrototype();
    bool isPrototype();
    TypeSignature* setId(std::string id);
    TypeSignature* setKeyId(std::string id);
    bool typeTargetIs(TypeSource other);
    bool typeSourceIs(TypeSource other);
    bool isOneOf(std::vector<TypeSource> typeSources);
    virtual bool isUnknown();
    virtual bool isInvalid();
    virtual bool isVoid();
    bool isUnknownOrInvalidOrVoid();
    virtual bool isLiteral();
    virtual bool isInvocable();
    virtual void copyFrom(TypeSignature* otherType);
    virtual TypeSource getTypeTarget();
    virtual TypeSignature* getTargetTypeSignature();
    virtual bool isEquivalentTo(TypeSignature* otherType);
    virtual TypeSignature* convertToVariableTypeSignature();
    virtual std::string toDetailString() = 0;
    virtual std::string toString() = 0;
    virtual TypeSource getTypeSource() = 0;
    virtual bool isEqualTo(TypeSignature* otherType) = 0;
    virtual void print() = 0;
};

#endif //JETLANG_TYPE_SIGNATURE_H
