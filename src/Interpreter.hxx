//
// Created by itsmanjeet on 11/6/23.
//

#ifndef SRCLANG_INTERPRETER_HXX
#define SRCLANG_INTERPRETER_HXX

#include "Value.hxx"
#include "Function.hxx"
#include "Builtin.hxx"
#include "Options.hxx"
#include "ByteCode.hxx"

namespace srclang {

    struct Language;

    struct Interpreter {
        struct Frame {
            typename std::vector<Byte>::iterator ip;
            Closure *closure;
            std::vector<Value>::iterator bp;
            std::vector<Value> defers;
        };


        int next_gc = 50;
        float GC_HEAP_GROW_FACTOR = 1.0;
        int LIMIT_NEXT_GC = 200;

        std::vector<Value> stack;
        std::vector<Value>::iterator sp;
        std::vector<Frame> frames;

        Language *language;

        typename std::vector<Frame>::iterator fp;
        std::vector<std::shared_ptr<DebugInfo>> debug_info;
        bool debug, break_;

        void error(std::string const &mesg);

        Interpreter(ByteCode &code, std::shared_ptr<DebugInfo> debugInfo, Language *language);

        ~Interpreter();

        void add_object(Value val);

        constexpr typename std::vector<Byte>::iterator &ip() { return (fp - 1)->ip; }

        typename std::vector<Frame>::iterator cur() { return (fp - 1); }

        void gc();

        bool isEqual(Value a, Value b);

        bool unary(Value a, OpCode op);

        bool binary(Value lhs, Value rhs, OpCode op);

        bool is_falsy(Value val);

        void print_stack();

        bool call_closure(Value callee, uint8_t count);

        bool call_builtin(Value callee, uint8_t count);

        bool call_typecast_int(uint8_t count);

        bool call_typecast_float(uint8_t count);

        bool call_typecast_char(uint8_t count);

        bool call_typecast_string(uint8_t count);

        bool call_typecast_error(uint8_t count);

        bool call_typecast_bool(uint8_t count);

        bool call_typecast_type(uint8_t count);

        bool call_typecast(Value callee, uint8_t count);

        bool call_native(Value callee, uint8_t count);

        bool call_bounded(Value callee, uint8_t count);

        bool call(uint8_t count);

        bool run();
    };

} // srclang

#endif //SRCLANG_INTERPRETER_HXX
