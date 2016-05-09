#include "transducer.h"
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

    Persistent<Function> Transducer::constructor;

    Transducer::Transducer() : value_() {
    }

    Transducer::~Transducer() {
    }

    void Transducer::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();
        // Prepare constructor template
        Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
        tpl->SetClassName(String::NewFromUtf8(isolate, "Transducer"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // member method prototypes
        NODE_SET_PROTOTYPE_METHOD(tpl, "addState", AddState);
        NODE_SET_PROTOTYPE_METHOD(tpl, "setStart", SetStart);
        NODE_SET_PROTOTYPE_METHOD(tpl, "addArc", AddArc);
        NODE_SET_PROTOTYPE_METHOD(tpl, "setFinal", SetFinal);

        // initialize constructor reference
        constructor.Reset(isolate, tpl->GetFunction());
        exports->Set(String::NewFromUtf8(isolate, "Transducer"),
               tpl->GetFunction());
    }
    void Transducer::New (const v8::FunctionCallbackInfo<Value>& args) {
        fst::StdVectorFst fst;
        Isolate* isolate = args.GetIsolate();

        if (args.IsConstructCall()) {
            // Invoked as constructor: `new Transducer(...)`
            Transducer* obj = new Transducer();
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            // Invoked as plain function `Transducer(...)`, turn into construct call.
            const int argc = 1;
            Local<Value> argv[argc] = { args[0] };
            Local<Function> cons = Local<Function>::New(isolate, constructor);
            args.GetReturnValue().Set(cons->NewInstance(argc, argv));
        }
    }
    void Transducer::AddState (const v8::FunctionCallbackInfo<Value>& args) {
        Transducer* obj = ObjectWrap::Unwrap<Transducer>(args.Holder());
        obj->value().AddState();

        args.GetReturnValue().SetUndefined();
    }
    void Transducer::SetStart (const v8::FunctionCallbackInfo<Value>& args) {
        // Isolate* isolate = args.GetIsolate();
        int start = args[0]->IsUndefined() ? 0 : args[0]->IntegerValue();
        Transducer* obj = ObjectWrap::Unwrap<Transducer>(args.Holder());
        obj->value().SetStart(start);
        args.GetReturnValue().SetUndefined();
    }
    void Transducer::AddArc (const v8::FunctionCallbackInfo<Value>& args) {
        int stateId = args[0]->IsUndefined() ? 0 : args[0]->IntegerValue();
        Transducer* obj = ObjectWrap::Unwrap<Transducer>(args.Holder());
        Arc* objArc = ObjectWrap::Unwrap<Arc>(args[1]->ToObject());
        obj->value().AddArc(stateId, objArc->value());
        args.GetReturnValue().SetUndefined();
    }
    void Transducer::SetFinal (const v8::FunctionCallbackInfo<Value>& args) {
        int stateId = args[0]->IsUndefined() ? 0 : args[0]->IntegerValue();
        double weight = args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
        Transducer* obj = ObjectWrap::Unwrap<Transducer>(args.Holder());
        obj->value().SetFinal(stateId, weight);
        args.GetReturnValue().SetUndefined();
    }
};
