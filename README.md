# picoproto
Abominably Tiny Protobuf File Parser in C++

## What is it?

Picoproto is a single file C++ implementation of protocol buffer parsing. It's designed to have no dependencies other than the standard library available in C++11, and to compile to a small binary size.

## Why did I build it?

Protocol Buffers can make large projects a lot easier by using a common language to describe data objects. Unfortunately this comes at a cost in executable size and complexity that can be too much for resource-limited platforms. On a reasonably-sized project, the base protobuf libraries and the access classes created for each type can easily take up several hundred kilobytes.

This frustrated me, because I wanted to retain the ease of data transfer that protobufs offer, even on systems that can't afford increases in executable size. In many cases, all I want to do is treat protobuf as a file format, and read data from those files as efficiently as possible. I don't need to write out protobuf objects, or have automatically-created access classes for each type. I also don't want to do any processing of .proto files at all, since that adds build complexity which can cause a lot of headaches when moving around platforms.

## How do you use it?

Look at the examples in `picoproto_test.cc` and `tf_to_dot.cc` to see how to invoke it.
