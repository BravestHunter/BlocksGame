#pragma once


template<typename T>
class DataBuffer
{
public:
  DataBuffer() : _data(nullptr), _size(0)
  {
  }

  DataBuffer(T* data, int size) : _data(data), _size(size)
  {
  }

  ~DataBuffer()
  {
    FreeMemory();
  }


  void SetData(T* data, int size)
  {
    FreeMemory();

    _data = data;
    _size = size;
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

  void FreeMemory()
  {
    if (_data != nullptr)
      delete _data;
  }
};
