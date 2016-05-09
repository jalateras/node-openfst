#ifndef NODEFST_ARC_H
#define NODEFST_ARC_H

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <fst/fstlib.h>

namespace NodeFst {
    class Arc : public node::ObjectWrap {
        public:
            static void Init(v8::Local<v8::Object> exports);
            inline fst::StdArc value() const { return value_; }
        private:
            explicit Arc(fst::StdArc a);
            ~Arc();

            static void New (const v8::FunctionCallbackInfo<v8::Value>& args);
            static v8::Persistent<v8::Function> constructor;
            fst::StdArc value_;
    };
};
#endif
