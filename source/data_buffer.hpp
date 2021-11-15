#pragma once


template<typename T>
class DataBuffer
{
public:
  DataBuffer(T* data, int size) : _data(data), _size(size)
  {
  }

  ~DataBuffer()
  {
    delete _data;
  }

  T* GetData() const
  {
    return _data;
  }

  int GetSize() const
  {
    return _size;
  }

private:
  T* _data;
  int _size;
};
