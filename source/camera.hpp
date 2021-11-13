#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 50.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera
{
public:
  Camera(glm::vec3 position = glm::vec3(-16.0f, -16.0f, 256.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

  glm::mat4 GetViewMatrix();
  float GetZoom();

  void ProcessKeyboard(Camera_Movement direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
  void ProcessMouseScroll(float yoffset);

private:
  glm::vec3 _position;
  glm::vec3 _front;
  glm::vec3 _right;
  glm::vec3 _up;

  float _yaw;
  float _pitch;

  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  void UpdateCameraVectors();
};
