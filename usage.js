"use strict";
const ivm = require("isolated-vm");
require(".");

const example = new ivm.NativeModule(require.resolve("."));

let isolate = new ivm.Isolate();
let context = isolate.createContextSync();
let global = context.global;

global.setSync("module", example.createSync(context).derefInto());

let script = isolate.compileScriptSync(`module.print(3)`);
script.runSync(context);
