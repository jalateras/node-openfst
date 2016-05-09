#include "arc.h"

namespace NodeFst {

    using v8::Function;
    using v8::FunctionCallbackInfo;
    using v8::FunctionTemplate;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::Persistent;
    using v8::String;
    using v8::Value;

    Persistent<Function> Arc::constructor;

    Arc::Arc(fst::StdArc a) : value_(a) {
    }

    Arc::~Arc() {
    }

    void Arc::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();
        // Prepare constructor template
        Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
        tpl->SetClassName(String::NewFromUtf8(isolate, "Arc"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // member method prototypes
        // ... none for now

        // initialize constructor reference
        constructor.Reset(isolate, tpl->GetFunction());
        exports->Set(String::NewFromUtf8(isolate, "Arc"),
               tpl->GetFunction());
    }

    //    ArcTpl(Label i, Label o, const Weight& w, StateId s)
    //    typedef W Weight; (float?)
    //    typedef int Label;
    //    typedef int StateId;
    void Arc::New (const v8::FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall()) {
            // Invoked as constructor: `new Arc(...)`
            int i = args[0]->IsUndefined() ? 0 : args[0]->IntegerValue();
            int o = args[1]->IsUndefined() ? 0 : args[1]->IntegerValue();
            double w = args[2]->IsUndefined() ? 0 : args[2]->NumberValue();
            int s = args[3]->IsUndefined() ? 0 : args[3]->IntegerValue();
            Arc* obj = new Arc(fst::StdArc(i, o, w, s));
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            // Invoked as plain function `Arc(...)`, turn into construct call.
            const int argc = 1;
            Local<Value> argv[argc] = { args[0] };
            Local<Function> cons = Local<Function>::New(isolate, constructor);
            args.GetReturnValue().Set(cons->NewInstance(argc, argv));
        }
    }

};
