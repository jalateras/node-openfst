#include <nan.h>
#include <fst/fstlib.h>

NAN_METHOD(Method) {
  // test proper link against fst lib
  fst::StdVectorFst fst;
}

NAN_MODULE_INIT(Module) {
  // all exports here
  Nan::Export(target, "hello", Method);
}

NODE_MODULE(openfst, Module);