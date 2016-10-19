# Scripting Engine

## Description

This directory contains all the bindings and wrappers for the JavaScript 
API to drive the engine.

## Pipeline

`Engine API (C++)` -> `V8 Binding (C++)` -> `node-gyp binding (JS)` -> `JS wrapper`

All the Engine's functionality can be wrapped around Google's V8 Engine 
which binds the C++ callbacks to a JavaScript interpreter.

We use NAN for the V8 bindings to ensure we are compatible with all V8 
releases.

Once the bindings are set they cna then be compiled through **node-gyp** 
to  create a **.node** executable.

The **.node** executable can then be used as a Node module which can be 
set various private methods.

Then create a JS wrapper that represent the public methods.

## Example
See sample for a working pipeline

## Creating a module

1. Setup GYP bindings
2. Include Package.json inputs
3. Write bindings
4. write JS binding wrapper using *bindings* (represents private methods)
5. write JS wrapper (represent public methods, what the consumer will use)

## TODO 

* Debugging
* Node Versions
* TypeScript