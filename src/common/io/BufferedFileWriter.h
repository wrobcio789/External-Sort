#pragma once
#include "File.h"

template <typename T>
class BufferedFileWriter
{
private:
	File* _file;
	Buffer<T>& _buffer;

	void _flushBuffer() {
		_file->write(_buffer.cast<char>());
		_buffer.size = 0;
	}

public:

	BufferedFileWriter(File* file, Buffer<T>& buffer) : _file(file), _buffer(buffer){}

	void write(T value) {
		_buffer.add(value);
		if (_buffer.isFull()) {
			_flushBuffer();
		}
	}

	void flush() {
		if (!_buffer.isEmpty()) {
			_flushBuffer();
		}
	}

};

