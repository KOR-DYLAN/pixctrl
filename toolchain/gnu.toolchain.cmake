# Set System Name
set(CMAKE_SYSTEM_NAME Linux)

# Set Toolchain
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)
set(CMAKE_LINKER ${CROSS_COMPILE}ld)
set(CMAKE_AR ${CROSS_COMPILE}ar)

######################################################
#               Set Default Option
######################################################
# Warnings
# list(APPEND OPT_WARN_LISTS "-Werror")                       # Treats all warnings as errors, causing compilation to fail if any warning is encountered.
list(APPEND OPT_WARN_LISTS "-Wall")                         # Enables a common set of warnings, including those about questionable constructs.
list(APPEND OPT_WARN_LISTS "-Wextra")                       # Enables additional warnings not covered by -Wall.
list(APPEND OPT_WARN_LISTS "-Wpedantic")                    # Issues all the warnings demanded by strict ISO C and ISO C++.
list(APPEND OPT_WARN_LISTS "-Wconversion")                  # Warns about implicit conversions that may alter a value.
list(APPEND OPT_WARN_LISTS "-Wshadow")                      # Warns when a variable declaration shadows one from an outer scope.
list(APPEND OPT_WARN_LISTS "-Wpointer-arith")               # Warns about pointer arithmetic on void * and function pointers.
list(APPEND OPT_WARN_LISTS "-Wcast-qual")                   # Warns if a cast removes a type qualifier (e.g., const).
list(APPEND OPT_WARN_LISTS "-Wcast-align")                  # Warns if a cast might result in misaligned data access.
list(APPEND OPT_WARN_LISTS "-Wwrite-strings")               # Causes string constants to be treated as arrays of const char.
list(APPEND OPT_WARN_LISTS "-Wmissing-prototypes")          # Warns if a global function is defined without a previous prototype declaration.
list(APPEND OPT_WARN_LISTS "-Wstrict-prototypes")           # Requires function prototypes to specify parameter types, not just empty parentheses.
list(APPEND OPT_WARN_LISTS "-Wold-style-definition")        # Warns about old-style (K&R) function definitions.
list(APPEND OPT_WARN_LISTS "-Wmissing-declarations")        # Warns if a global function is defined without a declaration.
list(APPEND OPT_WARN_LISTS "-Wredundant-decls")             # Warns if anything is declared more than once.
list(APPEND OPT_WARN_LISTS "-Wnested-externs")              # Warns if extern declarations are used inside a function.
list(APPEND OPT_WARN_LISTS "-Winline")                      # Warns if a function marked as inline cannot be inlined.
list(APPEND OPT_WARN_LISTS "-Wunreachable-code")            # Warns about code that will never be executed.
list(APPEND OPT_WARN_LISTS "-Wfloat-equal")                 # Warns if floating-point values are used in equality comparisons.
list(APPEND OPT_WARN_LISTS "-Wundef")                       # Warns if an undefined macro is used in #if directives.
list(APPEND OPT_WARN_LISTS "-Wbad-function-cast")           # Warns if a function call is cast to a non-matching type.
list(APPEND OPT_WARN_LISTS "-Wlogical-op")                  # Warns about suspicious use of logical operators.
list(APPEND OPT_WARN_LISTS "-Waggregate-return")            # Warns if a function returns a struct or union type.
list(APPEND OPT_WARN_LISTS "-Wstrict-aliasing")             # Warns about code that might break the strict aliasing rules.
list(APPEND OPT_WARN_LISTS "-Wvariadic-macros")             # Warns if variadic macros are used.
list(APPEND OPT_WARN_LISTS "-Wmultichar")                   # Warns if multi-character character constants are used.
list(APPEND OPT_WARN_LISTS "-Wc++-compat")                  # Warns about constructs that are not valid C++.
list(APPEND OPT_WARN_LISTS "-Wjump-misses-init")            # Warns if a jump bypasses variable initialization.
list(APPEND OPT_WARN_LISTS "-Wdouble-promotion")            # Warns if float is promoted to double.
list(APPEND OPT_WARN_LISTS "-Wunused-function")             # Warns if a function is defined but not used.
list(APPEND OPT_WARN_LISTS "-Wunused-variable")             # Warns if a variable is declared but not used.
list(APPEND OPT_WARN_LISTS "-Wunused-but-set-variable")     # Warns if a variable is set but not used.
list(APPEND OPT_WARN_LISTS "-Wunused-value")                # Warns if a value is computed but not used.
list(APPEND OPT_WARN_LISTS "-Wpacked")                      # Warns about improper uses of the packed attribute.
list(APPEND OPT_WARN_LISTS "-Wmissing-format-attribute")    # Warns if printf/scanf style functions are missing format attributes.
list(APPEND OPT_WARN_LISTS "-Wmissing-include-dirs")        # Warns if an #include directory does not exist.
list(APPEND OPT_WARN_LISTS "-Wunused")                      # Combines several -Wunused-* warnings.
list(APPEND OPT_WARN_LISTS "-Wdisabled-optimization")       # Warns if optimizations are disabled.
list(APPEND OPT_WARN_LISTS "-Wvla")                         # Warns if variable-length arrays are used.
list(APPEND OPT_WARN_LISTS "-Wno-unused-parameter")         # Disables warnings about unused parameters.
list(APPEND OPT_WARN_LISTS "-Wswitch-default")              # Warns if a switch statement does not have a default case.
list(APPEND OPT_WARN_LISTS "-Wmaybe-uninitialized")         # Warns if a variable might be used uninitialized.
list(APPEND OPT_WARN_LISTS "-Wpacked-bitfield-compat")      # Warns about potential issues with packed bitfields.
list(APPEND OPT_WARN_LISTS "-Wshift-overflow=2")            # Warns about shift operations that overflow, with level 2 providing more details.

# Join list elements with space
list(JOIN OPT_WARN_LISTS " " OPT_WARN)

# Common
set(CMAKE_C_FLAGS_INIT "-std=gnu99 -D_GNU_SOURCE ${OPT_WARN}")
set(CMAKE_CXX_FLAGS_INIT "-std=gnu99 -D_GNU_SOURCE ${OPT_WARN}")

# sanitize
list(APPEND OPT_COMMON_SANTINIZE_LISTS "-fno-omit-frame-pointer")   # This option tells the compiler to keep the frame pointer in the generated code. 
                                                                    # This can be useful for debugging because it allows stack traces to be more easily obtained and analyzed, making it easier to diagnose runtime errors.
list(APPEND OPT_COMMON_SANTINIZE_LISTS "-fno-sanitize-recover")     # This option disables recovery from detected sanitization errors, meaning that the program will stop execution immediately upon encountering an error that is detected by a sanitizer
                                                                    # (e.g., AddressSanitizer, MemorySanitizer). 
                                                                    # This ensures that issues are caught and addressed promptly.

if(ENABLE_SANTINIZE STREQUAL "ON")
    # Join list elements with space
    list(JOIN OPT_COMMON_SANTINIZE_LISTS " " OPT_COMMON_SANTINIZE)
    set(OPT_SANTINIZE "-fsanitize=${SANTINIZE}")
elseif(ENABLE_SANTINIZE STREQUAL "TRAB")
    # enable trap
    list(APPEND OPT_COMMON_SANTINIZE_LISTS "-fsanitize-undefined-trap-on-error")    # This option tells the compiler to generate traps (such as __builtin_trap()) when undefined behavior is detected by the UndefinedBehaviorSanitizer (UBSan). 
                                                                                    # Instead of just logging the error and continuing execution, the program will stop immediately, making it easier to catch and debug issues related to undefined behavior.

    # Join list elements with space
    list(JOIN OPT_COMMON_SANTINIZE_LISTS " " OPT_COMMON_SANTINIZE)
    set(OPT_SANTINIZE "-fsanitize=${SANTINIZE}")
endif()

# Debug
set(CMAKE_ASM_FLAGS_DEBUG "-O0 -g" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG   "-O0 -g ${OPT_COMMON_SANTINIZE} ${OPT_SANTINIZE}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g ${OPT_COMMON_SANTINIZE} ${OPT_SANTINIZE}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "" CACHE STRING "" FORCE)

# MinSizeRel
set(CMAKE_ASM_FLAGS_MINSIZEREL "-Os -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_MINSIZEREL   "-Os -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL "" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL "" CACHE STRING "" FORCE)

# Release
set(CMAKE_ASM_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE   "-O2 -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "" CACHE STRING "" FORCE)

# RelWithDebInfo
set(CMAKE_ASM_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO "" CACHE STRING "" FORCE)
