#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera_projection_type.hpp"


class Camera
{
public:
  Camera(
    CameraProjectionType projectionType,
    glm::vec3 worldUp,
    glm::vec3 position, 
    float yaw, 
    float pitch 
  );

  CameraProjectionType GetProjectionType();
  glm::vec3 GetWorldUp();
  glm::vec3 GetPosition();
  float GetYaw();
  float GetPitch();
  glm::vec3 GetForward();
  glm::vec3 GetRight();
  glm::vec3 GetUp();
  glm::mat4 GetView();
  glm::mat4 GetProjection();

  void SetProjectionType(CameraProjectionType projectionType);
  void SetWorldUp(glm::vec3 worldUp);
  void SetPosition(glm::vec3 position);
  void SetYaw(float yaw);
  void SetPitch(float pitch);

private:
  CameraProjectionType _projectionType;
  glm::vec3 _worldUp;
  
  glm::vec3 _position;
  float _yaw;
  float _pitch;

  bool _areDirectionVectorsDirty = true;
  glm::vec3 _forward = {};
  glm::vec3 _right = {};
  glm::vec3 _up {};

  bool _isViewDirty = true;
  glm::mat4 _view {};
  bool _isProjectionDirty = true;
  glm::mat4 _projection {};

  void RecalculateDirectionVectors();
};
