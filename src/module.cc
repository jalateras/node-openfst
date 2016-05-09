#include <nan.h>
#include <transducer.cc>
#include <arc.cc>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Hello(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Hello);
  NodeFst::Transducer::Init(exports);
  NodeFst::Arc::Init(exports);
}

NODE_MODULE(openfst, Init);
