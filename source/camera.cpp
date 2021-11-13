#include "camera.hpp"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
  : _front(glm::vec3(1.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
  _position = position;
  _yaw = yaw;
  _pitch = pitch;
  UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
  : _front(glm::vec3(1.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
  _position = glm::vec3(posX, posY, posZ);
  _yaw = yaw;
  _pitch = pitch;
  UpdateCameraVectors();
}


glm::mat4 Camera::GetViewMatrix()
{
  return glm::lookAt(_position, _position + _front, _up);
}

float Camera::GetZoom()
{
  return Zoom;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
  float velocity = MovementSpeed * deltaTime;
  if (direction == FORWARD)
    _position += _front * velocity;
  if (direction == BACKWARD)
    _position -= _front * velocity;
  if (direction == LEFT)
    _position -= _right * velocity;
  if (direction == RIGHT)
    _position += _right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  //_yaw -= xoffset;
  _yaw -= xoffset;
  _pitch += yoffset;

  if (constrainPitch)
  {
    if (_pitch > 89.0f)
      _pitch = 89.0f;
    if (_pitch < -89.0f)
      _pitch = -89.0f;
  }

  UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
  Zoom -= (float)yoffset;
  if (Zoom < 1.0f)
    Zoom = 1.0f;
  if (Zoom > 45.0f)
    Zoom = 45.0f;
}


void Camera::UpdateCameraVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
  front.y = sin(glm::radians(_yaw))* cos(glm::radians(_pitch));
  front.z = sin(glm::radians(_pitch));
  _front = glm::normalize(front);

  _right = glm::normalize(glm::cross(_front, glm::vec3(0.0f, 0.0f, 1.0f)));
  _up = glm::normalize(glm::cross(_right, _front));
}
