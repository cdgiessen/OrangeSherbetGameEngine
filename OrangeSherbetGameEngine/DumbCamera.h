

#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <CML\cml.h>



// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	cml::vec3f Position;
	cml::vec3f Front;
	cml::vec3f Up;
	cml::vec3f Right;
	cml::vec3f WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

	// Constructor with vectors
	Camera(cml::vec3f position = cml::VEC3_ZERO, cml::vec3f up = cml::VEC3_UP, GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(-cml::VEC3_FORWARD), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(-cml::VEC3_FORWARD), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		this->Position = cml::vec3f(posX, posY, posZ);
		this->WorldUp = cml::vec3f(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	cml::mat4f GetViewMatrix()
	{
		return createLookAt(this->Position, this->Position + this->Front, this->Up);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		GLfloat velocity = this->MovementSpeed * deltaTime;
		if (direction == FORWARD)
			this->Position += this->Front * velocity;
		if (direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yoffset)
	{
		if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yoffset;
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;
	}

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		cml::vec3f front;
		front.x = cos(cml::degToRad(this->Yaw)) * cos(cml::degToRad(this->Pitch));
		front.y = sin(cml::degToRad(this->Pitch));
		front.z = sin(cml::degToRad(this->Yaw)) * cos(cml::degToRad(this->Pitch));
		front.norm();
		// Also re-calculate the Right and Up vector
		this->Right = (cml::vec3f::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Right.norm();
		this->Up = (cml::vec3f::cross(this->Right, this->Front));
		this->Up.norm();
	}

	static cml::mat4f createLookAt(const cml::vec3f& eyePos, const cml::vec3f& centerPos, const cml::vec3f& upDir)
	{
		cml::vec3f forward, side, up;
		cml::mat4f m;

		forward = centerPos - eyePos;
		up = upDir;

		forward.norm();

		// Side = forward x up
		side = cml::vec3f::cross(up, forward);
		side.norm();

		// Recompute up as: up = side x forward
		up = cml::vec3f::cross(forward,side);

		m.at(0, 0) = side.x;
		m.at(1, 0) = side.y;
		m.at(2, 0) = side.z;

		m.at(0, 1) = up.x;
		m.at(1, 1) = up.y;
		m.at(2, 1) = up.z;

		m.at(0, 2) = -forward.x;
		m.at(1, 2) = -forward.y;
		m.at(2, 2) = -forward.z;

		m = m * cml::mat4f::createTranslationMatrix(cml::vec3f(-eyePos.x, -eyePos.y, -eyePos.z));
		return m;
	}
};
