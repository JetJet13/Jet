# Golden Master Test File

### Objective
The purpose of the `golden-master-test-file.jet` test file is to validate that every supported feature of the language works as expected.

### Language Features
1. Literals
   1. Integer
   2. Float
   3. Boolean
   4. Character
2. Strings
   1. Concatenation (`++`)
   2. Prototype Functions
       1. `append`
       2. `prepend`
       3. `take`
       4. `takeLast`
       5. `drop`
       6. `dropLast`
       7. `size`
       8. `empty`
       9. `tail`
3. Arrays
   1. Concatenation (`++`)
   2. Prototype Functions
      1. `append`
      2. `prepend`
      3. `take`
      4. `takeLast`
      5. `drop`
      6. `dropLast`
      7. `size`
      8. `empty`
      9. `tail`
4. Structs
5. Tuples 
6. Classes
   1. Multiple Constructors
   2. Access Modifiers (`public`, `private`)
   3. Static Modifier (`static`)
7. Enums
   1. Literal Value
   2. String Value
8. References
    1. Prototype Functions
       1. `refCount`
       2. `sameRefAs`
    2. Set Ref Value (`:=`)
9. Lambdas 
10. Modules
    1. Import
    2. Export
    3. Declaration
11. Built-In Functions
    1. `print(...vararg)`
    2. `range`
       1. `range(end: int)`
       2. `range(start: int, end: int)`
       3. `range(start: int, end: int, step: int)`
    3. `assert`
       1. `assert(bool)`
       2. `assert(bool, message)`
12. Logical Expressions 
13. Arithmetic Expressions
    1. Order of Operations (BEDMAS)
    2. addition (`+`)
    3. subtraction (`-`)
    4. multiplication (`*`)
    5. division (`/`)
    6. modulo (`mod`)
14. Unary Expressions
    1. `+` int or float
    2. `-` int or float
    3. `!` negate 
15. Comparator Expressions 
16. If Statements 
17. While Statements 
18. For-in Statements 
19. Functions
    1. Function Overrides
20. Procedures
    1. Procedure Overrides
21. Variables
    1. Constant (`const`)
    2. Mutable (`let`)
22. Global Variables
    1. Constant (`const`)
    2. Mutable (`let`)
23. Garbage Collection
    1. ARC (automatic reference counting)