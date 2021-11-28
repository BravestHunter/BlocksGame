#pragma once

#include "glew_entity.hpp"


class GlewVertexArray : public GlewEntity
{
public:
  GlewVertexArray();
  virtual ~GlewVertexArray() override;

  void Bind() const;
};
