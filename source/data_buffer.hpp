#pragma once


template<typename T>
class DataBuffer
{
public:
  DataBuffer::DataBuffer(T* data, int size) : _data(data), _size(size)
  {
  }

  DataBuffer::~DataBuffer()
  {
    delete _data;
  }

  T* DataBuffer::GetData() const
  {
    return _data;
  }

  int DataBuffer::GetSize() const
  {
    return _size;
  }

private:
  T* _data;
  int _size;
};
