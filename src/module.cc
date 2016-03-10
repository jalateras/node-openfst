#include <nan.h>

/*
NAN_METHOD(Method) {
  NanScope();
  NanReturnValue(String::New("world"));
}
*/

void Module(::v8::Handle<::v8::Object> exports) {
  // exports->Set(NanSymbol("hello"),
  // FunctionTemplate::New(Method)->GetFunction());
}

NODE_MODULE(openfst, Module);
