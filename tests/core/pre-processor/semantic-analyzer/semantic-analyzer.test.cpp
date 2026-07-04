//
// Created by Johny Georges on 2024-05-13.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/token/token-table.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/shared/utils/logger/logger.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "resources/type-signature-factory.h"
#include "../../../../src/core/type-signature/array-type-signature/array-type-signature.h"
#include "../../../../src/core/type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../../../../src/core/type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../../src/core/type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../../../src/core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../../../src/core/type-signature/invocable-type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"
#include "../../../../src/core/type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table-factory.h"

auto colorEnumTypeSignature = std::make_shared<EnumTypeSignature>(
        TypeSignatureFactory::stringLiteral,
        TypeSignatureMap<LiteralTypeSignature>({
               std::pair("Red", TypeSignatureFactory::stringLiteral),
               std::pair("Blue", TypeSignatureFactory::stringLiteral),
               std::pair("Green", TypeSignatureFactory::stringLiteral),
        }));

auto otherClassTypeSignature = std::make_shared<ClassTypeSignature>();
auto myClassTypeSignature = std::make_shared<ClassTypeSignature>();
auto testImplementationTypeSignature = std::make_shared<ClassTypeSignature>();
auto myInterfaceTypeSignature = std::make_shared<InterfaceTypeSignature>(
        TypeSignatureMap<TypeSignature>({
            std::pair("foo", TypeSignatureFactory::intLiteral),
            std::pair("bar", TypeSignatureFactory::boolLiteral),
            std::pair("hello", std::make_shared<LambdaTypeSignature>({}, TypeSignatureFactory::stringLiteral)),
            std::pair("structure", std::make_shared<StructTypeSignature>(TypeSignatureMap<TypeSignature>({
                                           std::pair("a", TypeSignatureFactory::intLiteral),
                                           std::pair("b", TypeSignatureFactory::intLiteral),
                                    })
            )),
            std::pair("bye", std::make_shared<LambdaTypeSignature>({
                                 std::make_shared<StructTypeSignature>(TypeSignatureMap<TypeSignature>({
                                     std::pair("a", TypeSignatureFactory::intLiteral),
                                     std::pair("b", TypeSignatureFactory::intLiteral),
                                 })),
                                 std::make_shared<StructTypeSignature>(TypeSignatureMap<TypeSignature>({
                                     std::pair("c", TypeSignatureFactory::boolLiteral),
                                     std::pair("d", TypeSignatureFactory::charLiteral),
                                 })),
                                },
                                TypeSignatureFactory::stringLiteral
            )),
            std::pair("myClassInstance", myClassTypeSignature),
        }));
        auto testInterfaceTypeSignature = std::make_shared<InterfaceTypeSignature>(
            TypeSignatureMap<TypeSignature>({
                std::pair("foo", TypeSignatureFactory::boolLiteral),
                std::pair("bar", TypeSignatureFactory::intLiteral),
                std::pair("getColor", std::make_shared<LambdaTypeSignature>({}, TypeSignatureFactory::stringLiteral)),
                std::pair("size", std::make_shared<LambdaTypeSignature>({}, TypeSignatureFactory::intLiteral)),
            })
        );
        auto twoTestInterfaceTypeSignature = std::make_shared<InterfaceTypeSignature>(
                TypeSignatureMap<TypeSignature>({
                    std::pair("magic", TypeSignatureFactory::boolLiteral),
                })
        );

std::unordered_map<int, std::shared_ptr<TypeSignature>> generateExpectedTypeSignatures() {

    otherClassTypeSignature
    ->addProperty("OtherClass_property_myIntOne", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature), false, false));

    myClassTypeSignature
    ->addProperty("MyClass_property_myIntOne", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, false))
    ->addProperty("MyClass_property_myIntTwo", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, false))
    ->addProperty("MyClass_property_myIntThree", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, false))
    ->addProperty("MyClass_property_myIntOneConst", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, true))
    ->addProperty("MyClass_property_myIntTwoConst", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, true))
    ->addProperty("MyClass_property_myIntThreeConst", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, true))
    ->addProperty("MyClass_property_fooOneStatic", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::protectedAccess, TypeSignatureFactory::intLiteral, true, false))
    ->addProperty("MyClass_property_fooTwoStatic", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::protectedAccess, TypeSignatureFactory::intLiteral, true, false))
    ->addProperty("MyClass_property_fooThreeStatic", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::protectedAccess, TypeSignatureFactory::intLiteral, true, false))
    ->addProperty("MyClass_property_mickOneStatic", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::privateAccess, TypeSignatureFactory::boolLiteral, true, true))
    ->addProperty("MyClass_property_mickTwoStatic", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::privateAccess, TypeSignatureFactory::boolLiteral, true, true))
    ->addProperty("MyClass_property_mickThreeStatic", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::privateAccess, TypeSignatureFactory::boolLiteral, true, true))
    ->addProperty("MyClass_property_initMyClass", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::privateAccess, std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature), false, false))
    ->addProperty("MyClass_property_myClassProp", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::privateAccess, std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature), false, false))
    ->addProperty("MyClass_property_otherClass", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::privateAccess, std::make_shared<NewClassInstanceTypeSignature>(otherClassTypeSignature), false, false))
    ->addConstructor(
        "MyClass_constructor_0",
        std::make_shared<ClassConstructorTypeSignature>(
            std::make_shared<ParameterListTypeSignature>({
                std::make_shared<ParameterListItemTypeSignature>("other", std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature))
    })))
    ->addConstructor(
        "MyClass_constructor_1",
        std::make_shared<ClassConstructorTypeSignature>(
            std::make_shared<ParameterListTypeSignature>({
                std::make_shared<ParameterListItemTypeSignature>("foo", TypeSignatureFactory::intLiteral)
    })))
    ->addMethod(
        "MyClass_method_create",
        std::make_shared<ClassMethodTypeSignature>(
            TypeSignatureFactory::publicAccess,
            std::make_shared<ParameterListTypeSignature>({
               std::make_shared<ParameterListItemTypeSignature>("foo", TypeSignatureFactory::intLiteral)
           }),
           true,
            std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature)
       )
   )
    ->addMethod(
        "MyClass_method_doSomething",
        std::make_shared<ClassMethodTypeSignature>(
            TypeSignatureFactory::protectedAccess,
            std::make_shared<ParameterListTypeSignature>({
               std::make_shared<ParameterListItemTypeSignature>("other", std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature))
            }),
            true,
            std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature)
        )
    )
    ->addMethod(
        "MyClass_method_doSomethingElse",
        std::make_shared<ClassMethodTypeSignature>(
            TypeSignatureFactory::privateAccess,
            std::make_shared<ParameterListTypeSignature>(),
            true,
            std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature)
        )
    )
    ->addMethod(
        "MyClass_method_isValid",
        std::make_shared<ClassMethodTypeSignature>(
            TypeSignatureFactory::publicAccess,
            std::make_shared<ParameterListTypeSignature>(),
            false,
            TypeSignatureFactory::boolLiteral
        )
    )
    ->addMethod(
        "MyClass_method_setBar",
        std::make_shared<ClassMethodTypeSignature>(
            TypeSignatureFactory::protectedAccess,
            std::make_shared<ParameterListTypeSignature>({
                std::make_shared<ParameterListItemTypeSignature>("bar", TypeSignatureFactory::boolLiteral)
            }),
            false,
            std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature)
        )
    )
    ->addMethod(
        "MyClass_method_hello",
        std::make_shared<ClassMethodTypeSignature>(
            TypeSignatureFactory::privateAccess,
            std::make_shared<ParameterListTypeSignature>(),
            false,
            TypeSignatureFactory::stringLiteral
        )
    )
    ->addMethod(
        "MyClass_method_helloBar",
        std::make_shared<ClassMethodTypeSignature>(
            TypeSignatureFactory::privateAccess,
            std::make_shared<ParameterListTypeSignature>(),
            false
        )
    );

    testImplementationTypeSignature
    ->addProperty("TestImplementation_property_foo", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::boolLiteral, false, false))
    ->addProperty("TestImplementation_property_bar", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, false))
    ->addProperty("TestImplementation_property_color", std::make_shared<ClassPropertyTypeSignature>(TypeSignatureFactory::privateAccess, TypeSignatureFactory::stringLiteral, false, false))
    ->addConstructor(
        "TestImplementation_constructor_0",
        std::make_shared<ClassConstructorTypeSignature>(
                std::make_shared<ParameterListTypeSignature>({
                    std::make_shared<ParameterListItemTypeSignature>("color", TypeSignatureFactory::stringLiteral)
    })))
    ->addMethod(
        "TestImplementation_method_getColor",
        std::make_shared<ClassMethodTypeSignature>(
                TypeSignatureFactory::privateAccess,
                std::make_shared<ParameterListTypeSignature>(),
                false,
                TypeSignatureFactory::stringLiteral
        )
    )
    ->addMethod(
        "TestImplementation_method_size",
        std::make_shared<ClassMethodTypeSignature>(
                TypeSignatureFactory::publicAccess,
                std::make_shared<ParameterListTypeSignature>(),
                false,
                TypeSignatureFactory::intLiteral
        )
    );


    return {
            {1, TypeSignatureFactory::intLiteral},
            {2, TypeSignatureFactory::floatLiteral},
            {3, TypeSignatureFactory::stringLiteral},
            {4, TypeSignatureFactory::charLiteral},
            {5, TypeSignatureFactory::boolLiteral},
            {6, TypeSignatureFactory::boolLiteral},
            {7, TypeSignatureFactory::intLiteral},
            {8, TypeSignatureFactory::intLiteral},
            {9, TypeSignatureFactory::intLiteral},
            {10, TypeSignatureFactory::intLiteral},
            {11, TypeSignatureFactory::floatLiteral},
            {12, TypeSignatureFactory::intLiteral},
            {13, TypeSignatureFactory::stringLiteral},
            {14, TypeSignatureFactory::intLiteral},
            {15, TypeSignatureFactory::floatLiteral},
            {16, TypeSignatureFactory::intLiteral},
            {17, TypeSignatureFactory::intLiteral},
            {18, TypeSignatureFactory::intLiteral},
            {19, TypeSignatureFactory::floatLiteral},
            {20, TypeSignatureFactory::floatLiteral},
            {21, TypeSignatureFactory::intLiteral},
            {22, TypeSignatureFactory::intLiteral},
            {23, TypeSignatureFactory::intLiteral},
            {24, TypeSignatureFactory::intLiteral},
            {25, TypeSignatureFactory::floatLiteral},
            {26, TypeSignatureFactory::floatLiteral},
            {27, TypeSignatureFactory::intLiteral},
            {28, TypeSignatureFactory::boolLiteral},
            {29, TypeSignatureFactory::boolLiteral},
            {30, TypeSignatureFactory::boolLiteral},
            {31, TypeSignatureFactory::boolLiteral},
            {32, TypeSignatureFactory::boolLiteral},
            {33, TypeSignatureFactory::boolLiteral},
            {34, TypeSignatureFactory::boolLiteral},
            {35, TypeSignatureFactory::boolLiteral},
            {36, TypeSignatureFactory::boolLiteral},
            {37, TypeSignatureFactory::boolLiteral},
            {38, TypeSignatureFactory::boolLiteral},
            {39, TypeSignatureFactory::boolLiteral},
            {40, TypeSignatureFactory::boolLiteral},
            {41, TypeSignatureFactory::boolLiteral},
            {42, TypeSignatureFactory::boolLiteral},
            {43, TypeSignatureFactory::boolLiteral},
            {44, TypeSignatureFactory::boolLiteral},
            {45, TypeSignatureFactory::boolLiteral},
            {46, TypeSignatureFactory::boolLiteral},
            {47, TypeSignatureFactory::boolLiteral},
            {48, TypeSignatureFactory::boolLiteral},
            {49, TypeSignatureFactory::intLiteral},
            {50, TypeSignatureFactory::intLiteral},
            {51, TypeSignatureFactory::intLiteral},
            {52, TypeSignatureFactory::intLiteral},
            {53, TypeSignatureFactory::intLiteral},
            {54, TypeSignatureFactory::boolLiteral},
            {55, TypeSignatureFactory::boolLiteral},
            {56, TypeSignatureFactory::boolLiteral},
            {57, TypeSignatureFactory::boolLiteral},
            {58, TypeSignatureFactory::intLiteral},
            {59, TypeSignatureFactory::boolLiteral},
            {60, TypeSignatureFactory::boolLiteral},
            {61, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {62, TypeSignatureFactory::intLiteral},
            {63, TypeSignatureFactory::intLiteral},
            {64, std::make_shared<ArrayTypeSignature>(std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral))},
            {65, std::make_shared<ArrayTypeSignature>(std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral))},
            {66, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {67, TypeSignatureFactory::intLiteral},
            {68, TypeSignatureFactory::intLiteral},
            {69, std::make_shared<StructTypeSignature>(
                    TypeSignatureMap<TypeSignature>({
                        std::pair("i", TypeSignatureFactory::intLiteral),
                        std::pair("f", TypeSignatureFactory::floatLiteral),
                        std::pair("world", TypeSignatureFactory::boolLiteral),
                        std::pair("character", TypeSignatureFactory::charLiteral),
                        std::pair("str", TypeSignatureFactory::stringLiteral),
                        std::pair("identifier", TypeSignatureFactory::boolLiteral),
                        std::pair("array", std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)),
                        std::pair("arrAccess", TypeSignatureFactory::intLiteral),
                        std::pair("obj", std::make_shared<StructTypeSignature>(
                            TypeSignatureMap<TypeSignature>({
                                std::pair("test", TypeSignatureFactory::intLiteral),
                                std::pair("nest", std::make_shared<StructTypeSignature>(
                                    TypeSignatureMap<TypeSignature>({
                                        std::pair("value", TypeSignatureFactory::boolLiteral),
                                    })
                                )),
                            })
                        )),
                        std::pair("binary", TypeSignatureFactory::intLiteral),
                        std::pair("logical", TypeSignatureFactory::boolLiteral),
                        std::pair("unary", TypeSignatureFactory::boolLiteral),
                    })
            )},
            {70, TypeSignatureFactory::boolLiteral},
            {71, TypeSignatureFactory::intLiteral},
            {72, TypeSignatureFactory::boolLiteral},
            {73, std::make_shared<ArrayTypeSignature>(
                    std::make_shared<StructTypeSignature>(
                        TypeSignatureMap({
                             std::pair("hello", TypeSignatureFactory::stringLiteral),
                             std::pair("test", TypeSignatureFactory::intLiteral),
                        })
                    )
            )},
            {74, TypeSignatureFactory::stringLiteral},
            {75, std::make_shared<StructTypeSignature>(
                    TypeSignatureMap({
                         std::pair("array",
                               std::make_shared<ArrayTypeSignature>(
                                   std::make_shared<StructTypeSignature>(
                                       TypeSignatureMap({
                                            std::pair("hello", TypeSignatureFactory::stringLiteral),
                                            std::pair("test", TypeSignatureFactory::intLiteral),
                                       })
                                   )
                               )),
                         std::pair("arrNested", std::make_shared<ArrayTypeSignature>(
                             std::make_shared<ArrayTypeSignature>(
                                 std::make_shared<StructTypeSignature>(
                                     TypeSignatureMap({
                                          std::pair("hello", TypeSignatureFactory::stringLiteral),
                                          std::pair("test", TypeSignatureFactory::intLiteral),
                                     })
                                 )
                             )
                         )),
                   })
            )},
            {76, TypeSignatureFactory::stringLiteral},
            {77, TypeSignatureFactory::stringLiteral},
            {78, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                       TypeSignatureFactory::createIntParameter("x"),
                       TypeSignatureFactory::createIntParameter("y")
                    }),
                    TypeSignatureFactory::intLiteral
            )},
            {79, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>(),
                    TypeSignatureFactory::intLiteral
            )},
            {80, std::make_shared<ProcedureTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                        TypeSignatureFactory::createIntParameter("num")
                    })
            )},
            {81, std::make_shared<ProcedureTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>()
            )},
            {82, std::make_shared<ProcedureTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>()
            )},
            {83, std::make_shared<EnumAccessTypeSignature>(
                    colorEnumTypeSignature,
                    "Red"
            )},
            {84, colorEnumTypeSignature },
            {85, std::make_shared<EnumTypeSignature>(
                    TypeSignatureFactory::charLiteral,
                    TypeSignatureMap<LiteralTypeSignature>({
                       std::pair("Red", TypeSignatureFactory::charLiteral),
                       std::pair("Blue", TypeSignatureFactory::charLiteral),
                       std::pair("Green", TypeSignatureFactory::charLiteral),
                    }))
            },
            {86, std::make_shared<EnumTypeSignature>(
                    TypeSignatureFactory::intLiteral,
                    TypeSignatureMap<LiteralTypeSignature>({
                       std::pair("Zero", TypeSignatureFactory::intLiteral),
                       std::pair("One", TypeSignatureFactory::intLiteral),
                       std::pair("Two", TypeSignatureFactory::intLiteral),
                    }))
            },
            {87, TypeSignatureFactory::boolLiteral},
            {88, TypeSignatureFactory::boolLiteral},
            {89, std::make_shared<TupleTypeSignature>({
                    TypeSignatureFactory::stringLiteral,
                    TypeSignatureFactory::intLiteral,
                    TypeSignatureFactory::intLiteral
            })},
            {90, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>(),
                    TypeSignatureFactory::stringLiteral
            )},
            {91, std::make_shared<LambdaTypeSignature>(
                    {
                        colorEnumTypeSignature
                    },
                    colorEnumTypeSignature
            )},
            {92, std::make_shared<LambdaTypeSignature>(
                    {
                       TypeSignatureFactory::intLiteral,
                       TypeSignatureFactory::intLiteral,
                    },
                    TypeSignatureFactory::boolLiteral
            )},
            {93, std::make_shared<LambdaTypeSignature>(
                    {
                        TypeSignatureFactory::intLiteral,
                    },
                    TypeSignatureFactory::intLiteral
            )},
            {94, std::make_shared<LambdaTypeSignature>(
                    {
                        TypeSignatureFactory::intLiteral,
                    },
                    std::make_shared<LambdaTypeSignature>(
                            {
                                TypeSignatureFactory::intLiteral,
                            },
                            std::make_shared<LambdaTypeSignature>(
                                {
                                    TypeSignatureFactory::intLiteral,
                                },
                                TypeSignatureFactory::intLiteral
                            ))
            )},
            {95, TypeSignatureFactory::boolLiteral },
            {96, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                       std::make_shared<ParameterListItemTypeSignature>(
                           "x",
                           TypeSignatureFactory::intLiteral
                       ),
                       std::make_shared<ParameterListItemTypeSignature>(
                           "lambda",
                           std::make_shared<LambdaTypeSignature>(
                               { TypeSignatureFactory::intLiteral },
                               TypeSignatureFactory::boolLiteral)
                       ),
                    }),
                    TypeSignatureFactory::boolLiteral
            )},
            {97, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                       std::make_shared<ParameterListItemTypeSignature>(
                           "lambda",
                           std::make_shared<LambdaTypeSignature>(
                               {
                                   TypeSignatureFactory::intLiteral,
                                   TypeSignatureFactory::intLiteral
                               },
                               std::make_shared<LambdaTypeSignature>(
                                   {
                                       TypeSignatureFactory::intLiteral
                                   },
                                   TypeSignatureFactory::boolLiteral
                               )
                           )
                       ),
                    }),
                    TypeSignatureFactory::boolLiteral
            )},
            {98, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>(),
                    std::make_shared<LambdaTypeSignature>(
                        {},
                        TypeSignatureFactory::intLiteral
                    )
            )},
            {99, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>(),
                    std::make_shared<LambdaTypeSignature>(
                        { TypeSignatureFactory::intLiteral },
                        TypeSignatureFactory::intLiteral
                    )
            )},
            {100, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>(),
                    TypeSignatureFactory::boolLiteral
            )},
            {101, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                       std::make_shared<ParameterListItemTypeSignature>(
                           "x",
                           std::make_shared<LambdaTypeSignature>(
                               { TypeSignatureFactory::intLiteral },
                               TypeSignatureFactory::boolLiteral
                           )
                       )
                    }),
                    TypeSignatureFactory::boolLiteral
            )},
            {102, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                       std::make_shared<ParameterListItemTypeSignature>(
                           "x",
                           std::make_shared<LambdaTypeSignature>()
                       ),
                       std::make_shared<ParameterListItemTypeSignature>(
                           "y",
                           std::make_shared<LambdaTypeSignature>({ colorEnumTypeSignature })
                       )
                   }),
                    TypeSignatureFactory::boolLiteral
            )},
            {103, std::make_shared<LambdaTypeSignature>(
                    {},
                    TypeSignatureFactory::intLiteral
            )},
            {104, std::make_shared<LambdaTypeSignature>(
                    {
                       TypeSignatureFactory::intLiteral
                    }
            )},
            {105, std::make_shared<LambdaTypeSignature>()},
            {106, TypeSignatureFactory::intLiteral},
            {107, TypeSignatureFactory::floatLiteral},
            {108, TypeSignatureFactory::charLiteral},
            {109, TypeSignatureFactory::stringLiteral},
            {110, TypeSignatureFactory::boolLiteral},
            {111, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {112, std::make_shared<LambdaTypeSignature>(
                    { TypeSignatureFactory::intLiteral },
                    TypeSignatureFactory::boolLiteral
            )},
            {113, std::make_shared<LambdaTypeSignature>(
                    { TypeSignatureFactory::intLiteral }
            )},
            {114, std::make_shared<TupleTypeSignature>({
                     TypeSignatureFactory::intLiteral,
                     TypeSignatureFactory::intLiteral
            })},
            {115, colorEnumTypeSignature},
            {116, std::make_shared<NewClassInstanceTypeSignature>(myClassTypeSignature)},
            {117, otherClassTypeSignature},
            {118, myClassTypeSignature},
            {119, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                       TypeSignatureFactory::createIntParameter("n")
                    }),
                    TypeSignatureFactory::intLiteral
            )},
            {120, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>(),
                    TypeSignatureFactory::intLiteral
            )},
            {121, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>(),
                    TypeSignatureFactory::intLiteral
            )},
            {122, std::make_shared<ArrayTypeSignature>(
                    TypeSignatureFactory::intLiteral
            )},
            {123, std::make_shared<StructTypeSignature>(
                    TypeSignatureMap({
                        std::pair("bar", TypeSignatureFactory::charLiteral),
                    })
            )},
            {124, std::make_shared<ArrayTypeSignature>(
                    TypeSignatureFactory::intLiteral
            )},
            {125, TypeSignatureFactory::refIntLiteral},
            {126, TypeSignatureFactory::refFloatLiteral},
            {127, TypeSignatureFactory::refStringLiteral},
            {128, TypeSignatureFactory::refBoolLiteral},
            {129, TypeSignatureFactory::refCharLiteral},
            {130, std::make_shared<RefTypeSignature>(
                    std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)
            )},
            {131, std::make_shared<RefTypeSignature>(
                    std::make_shared<StructTypeSignature>(
                        TypeSignatureMap({
                            std::pair("a", TypeSignatureFactory::intLiteral),
                            std::pair("b", TypeSignatureFactory::boolLiteral),
                        })
                    )
            )},
            {132, std::make_shared<RefTypeSignature>(
                    std::make_shared<TupleTypeSignature>({
                        TypeSignatureFactory::stringLiteral,
                        TypeSignatureFactory::boolLiteral,
                        TypeSignatureFactory::intLiteral
                    })
            )},
            {133, std::make_shared<RefTypeSignature>(
                    std::make_shared<StructTypeSignature>(
                        TypeSignatureMap({
                            std::pair("bar", TypeSignatureFactory::charLiteral),
                        })
                    )
            )},
            {134, TypeSignatureFactory::refCharLiteral},
            {135, TypeSignatureFactory::refIntLiteral},
            {136, TypeSignatureFactory::refStringLiteral},
            {137, std::make_shared<ArrayTypeSignature>(
                    TypeSignatureFactory::refIntLiteral
            )},
            {138, std::make_shared<StructTypeSignature>(
                        TypeSignatureMap({
                            std::pair("a", TypeSignatureFactory::refIntLiteral),
                            std::pair("b", TypeSignatureFactory::refCharLiteral),
                        })
            )},
            {139, std::make_shared<TupleTypeSignature>({
                        TypeSignatureFactory::refStringLiteral,
                        TypeSignatureFactory::refBoolLiteral,
                        TypeSignatureFactory::refIntLiteral
            })},
            {140, std::make_shared<StructTypeSignature>(
                    TypeSignatureMap({
                        std::pair("bar", TypeSignatureFactory::charLiteral),
                    })
            )},
            {141, TypeSignatureFactory::charLiteral},
            {142, TypeSignatureFactory::intLiteral},
            {143, TypeSignatureFactory::stringLiteral},
            {144, std::make_shared<FunctionTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                        TypeSignatureFactory::createRefIntParameter("x"),
                        TypeSignatureFactory::createRefBoolParameter("y"),
                        TypeSignatureFactory::createParameter(
                            "z",
                            std::make_shared<RefTypeSignature>(
                                std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)
                            )
                        )
                    }),
                    TypeSignatureFactory::refIntLiteral
            )},
            {145, TypeSignatureFactory::refCharLiteral},
            {146, std::make_shared<LambdaTypeSignature>(
                    {
                        TypeSignatureFactory::refIntLiteral,
                    },
                    TypeSignatureFactory::intLiteral
            )},
            {147, std::make_shared<LambdaTypeSignature>(
                    {
                        TypeSignatureFactory::refIntLiteral,
                    },
                    TypeSignatureFactory::refIntLiteral
            )},
            {148, std::make_shared<RefTypeSignature>(
                    std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)
            )},
            {149, std::make_shared<RefTypeSignature>(
                    std::make_shared<StructTypeSignature>(
                        TypeSignatureMap({
                            std::pair("bar", TypeSignatureFactory::charLiteral),
                        })
                    )
            )},
            {150, std::make_shared<RefTypeSignature>(TypeSignatureFactory::charLiteral)},
            {151, std::make_shared<RefTypeSignature>(TypeSignatureFactory::intLiteral)},
            {152, std::make_shared<RefTypeSignature>(TypeSignatureFactory::stringLiteral)},
            {153, TypeSignatureFactory::stringLiteral},
            {154, TypeSignatureFactory::stringLiteral},
            {155, TypeSignatureFactory::stringLiteral},
            {156, TypeSignatureFactory::stringLiteral},
            {157, TypeSignatureFactory::stringLiteral},
            {158, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {159, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {160, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {161, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {162, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {163, TypeSignatureFactory::intLiteral},
            {164, TypeSignatureFactory::intLiteral},
            {165, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {166, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {167, std::make_shared<ArrayTypeSignature>(TypeSignatureFactory::intLiteral)},
            {168, std::make_shared<StructTypeSignature>(
                    TypeSignatureMap({
                        std::pair("foo", std::make_shared<LambdaTypeSignature>(
                                {
                                    TypeSignatureFactory::intLiteral,
                                },
                                TypeSignatureFactory::intLiteral
                        )),
                        std::pair("bar", std::make_shared<LambdaTypeSignature>(
                                {},
                                TypeSignatureFactory::intLiteral
                        )),
                        std::pair("foo2", std::make_shared<LambdaTypeSignature>(
                                {
                                    TypeSignatureFactory::intLiteral,
                                },
                                TypeSignatureFactory::intLiteral
                        )),
                    })
                    )
            },
            {169, std::make_shared<TupleTypeSignature>({
                         std::make_shared<LambdaTypeSignature>(
                                 {
                                     TypeSignatureFactory::intLiteral,
                                 },
                                 TypeSignatureFactory::intLiteral
                         ),
                         std::make_shared<LambdaTypeSignature>(
                                 {},
                                 TypeSignatureFactory::intLiteral
                         ),
                         std::make_shared<LambdaTypeSignature>(
                                 {
                                     TypeSignatureFactory::intLiteral,
                                 },
                                 TypeSignatureFactory::intLiteral
                         )
            })},
            {170, TypeSignatureFactory::intLiteral},
            {171, myInterfaceTypeSignature},
            {172, std::make_shared<StructTypeSignature>(
                        TypeSignatureMap<TypeSignature>({
                            std::pair("a", TypeSignatureFactory::boolLiteral),
                            std::pair("c", TypeSignatureFactory::charLiteral),
                        })
                    )
            },
            {173, myInterfaceTypeSignature},
            {174, std::make_shared<ProcedureTypeSignature>(
                    std::make_shared<ParameterListTypeSignature>({
                       std::make_shared<ParameterListItemTypeSignature>(
                           "myStruct",
                           std::make_shared<StructTypeSignature>(
                                   TypeSignatureMap<TypeSignature>({
                                        std::pair("a", TypeSignatureFactory::boolLiteral),
                                        std::pair("b", std::make_shared<StructTypeSignature>(
                                                TypeSignatureMap<TypeSignature>({
                                                    std::pair("foo", TypeSignatureFactory::intLiteral),
                                                    std::pair("bar", TypeSignatureFactory::boolLiteral),
                                                })
                                        )),
                                   })
                           )
                       )
                   })
            )},
            {175, testInterfaceTypeSignature},
            {176, twoTestInterfaceTypeSignature},
            {177, testImplementationTypeSignature},
            {178, testInterfaceTypeSignature},
            {179, twoTestInterfaceTypeSignature},

            {180, TypeSignatureFactory::stringLiteral},
            {181, std::make_shared<LambdaTypeSignature>({}, TypeSignatureFactory::boolLiteral)},
            {182, TypeSignatureFactory::floatLiteral},
            {183, std::make_shared<StructTypeSignature>(
                    TypeSignatureMap<TypeSignature>({
                        std::pair("x", TypeSignatureFactory::intLiteral),
                        std::pair("y", TypeSignatureFactory::intLiteral),
                    })
            )},
            {184, std::make_shared<StructTypeSignature>(
                    TypeSignatureMap<TypeSignature>({
                        std::pair("x", TypeSignatureFactory::intLiteral),
                        std::pair("y", TypeSignatureFactory::intLiteral),
                    })
            )},
            {185, std::make_shared<ArrayTypeSignature>(
                    std::make_shared<StructTypeSignature>(
                        TypeSignatureMap<TypeSignature>({
                            std::pair("foo", TypeSignatureFactory::boolLiteral),
                            std::pair("nested", std::make_shared<StructTypeSignature>(
                                    TypeSignatureMap<TypeSignature>({
                                        std::pair("bar", TypeSignatureFactory::intLiteral),
                                    })
                            )),
                        })
                    )
            )},
    };
}

TEST_CASE( "should print the expected type signatures" ) {
    std::string filePath = "./semantic-analyzer-test-file.jet";
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto fileScope = syntaxAnalyzer.analyze(filePath)->getFileScope();
    auto typeSignatureLookupTable = TypeSignatureLookupTableFactory::createForModule();
    auto semanticAnalyzer = SemanticAnalyzer();
    auto fileNode = new ASTFileNode(fileScope->getScope(), filePath, fileScope->getImports(), fileScope->getModule());
    auto typeCheckerResult = semanticAnalyzer.analyze(fileNode, typeSignatureLookupTable);
    auto expectedTypeSignatures = generateExpectedTypeSignatures();
    Logger::log("===== TEST LOGS =====");
    typeSignatureLookupTable->dump();
    for (int i = 0; i < 185; i++) {
        auto declaration = fileNode->getBody()->at(i);
        auto typeSignature = typeSignatureLookupTable->find(declaration->getId());
        auto expectedTypeSignature = expectedTypeSignatures[i + 1];
        Logger::log("=====", i + 1, declaration->toString(), "=====");
        Logger::log("ID -", declaration->getId());
        typeSignature->print();
        auto result = typeSignature->isEqualTo(expectedTypeSignature);
        Logger::log("RESULT =", result);
        if (!result) {
            expectedTypeSignature->print();
        }
        REQUIRE(typeSignature->isEqualTo(expectedTypeSignature));
        Logger::log("====================================");
    }
    typeCheckerResult.printErrors();
    REQUIRE(typeCheckerResult.ok());
}