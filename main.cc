#include <nan.h>
#include <stdio.h>
#include <isolated_vm.h>

using namespace v8;

NAN_METHOD(print) {
	if (!info[0]->IsString()) {
        return Nan::ThrowError("Must pass a string");
    }

    Nan::Utf8String path(info[0]);

    printf("Printed from C++: %s\n", *path);
}

ISOLATED_VM_MODULE void InitForContext(Isolate *isolate, Local<Context> context, Local<Object> target) {
	Nan::Set(target, Nan::New("print").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(print)).ToLocalChecked());
}

NAN_MODULE_INIT(init) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  InitForContext(isolate, isolate->GetCurrentContext(), target);
}

NODE_MODULE(native, init);