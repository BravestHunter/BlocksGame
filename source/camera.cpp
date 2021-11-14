#include "camera.hpp"


Camera::Camera(
  CameraProjectionType projectionType,
  glm::vec3 worldUp,
  glm::vec3 position,
  float yaw,
  float pitch
) :
  _projectionType(projectionType),
  _worldUp(worldUp),
  _position(position),
  _yaw(yaw),
  _pitch(pitch)
{
}


CameraProjectionType Camera::GetProjectionType()
{
  return _projectionType;
}

glm::vec3 Camera::GetWorldUp()
{
  return _worldUp;
}

glm::vec3 Camera::GetPosition()
{
  return _position;
}

float Camera::GetYaw()
{
  return _yaw;
}

float Camera::GetPitch()
{
  return _pitch;
}

glm::vec3 Camera::GetForward()
{
  if (_areDirectionVectorsDirty)
    RecalculateDirectionVectors();

  return _forward;
}

glm::vec3 Camera::GetRight()
{
  if (_areDirectionVectorsDirty)
    RecalculateDirectionVectors();

  return _right;
}

glm::vec3 Camera::GetUp()
{
  if (_areDirectionVectorsDirty)
    RecalculateDirectionVectors();

  return _up;
}

glm::mat4 Camera::GetView()
{
  if (_areDirectionVectorsDirty)
    RecalculateDirectionVectors();

  if (_isViewDirty)
  {
    _view = glm::lookAt(_position, _position + _forward, _up);

    _isViewDirty = false;
  }

  return _view;
}

glm::mat4 Camera::GetProjection()
{
  if (_isProjectionDirty)
  {
    if (_projectionType == CameraProjectionType::Perspective)
    {
      _projection = glm::perspective(glm::radians(45.0f), 48.0f / 27, 0.1f, 1000.0f);
    }
    else
    {
      throw new std::exception("Othographic CameraProjectionType not supported");
    }

    _isProjectionDirty = false;
  }

  return _projection;
}


void Camera::SetProjectionType(CameraProjectionType projectionType)
{
  if (_projectionType == projectionType)
    return;

  _projectionType = projectionType;

  _isProjectionDirty = true;
}

void Camera::SetWorldUp(glm::vec3 worldUp)
{
  if (_worldUp == worldUp)
    return;

  _worldUp = worldUp;

  _areDirectionVectorsDirty = true;
}

void Camera::SetPosition(glm::vec3 position)
{
  if (_position == position)
    return;

  _position = position;

  _isViewDirty = true;
}

void Camera::SetYaw(float yaw)
{
  if (_yaw == yaw)
    return;

  _yaw = yaw;

  _areDirectionVectorsDirty = true;
}

void Camera::SetPitch(float pitch)
{
  if (_pitch == pitch)
    return;

  _pitch = pitch;

  if (_pitch > 89.9f)
    _pitch = 89.9f;
  if (_pitch < -89.9f)
    _pitch = -89.9f;

  _areDirectionVectorsDirty = true;
}


void Camera::RecalculateDirectionVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  front.y = sin(glm::radians(_yaw))* cos(glm::radians(_pitch));
  front.z = sin(glm::radians(_pitch));

  _forward = glm::normalize(front);
  _right = glm::normalize(glm::cross(_forward, _worldUp));
  _up = glm::normalize(glm::cross(_right, _forward));

  _areDirectionVectorsDirty = false;
  _isViewDirty = true;
}
