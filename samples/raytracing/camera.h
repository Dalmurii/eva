#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "math_types.h"
#include "input.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEGREE (M_PI / 180.0)

// Forward declaration
class InputEngine;

class PinholeCamera
{
    // Camera Intrinsic Parameters
    float fovY = 60.0f;
    float screenWidth = 1.0f;
    float screenHeight = 1.0f;

    // Camera Extrinsic Parameters
    float3 cameraPos;
    float3 cameraX;
    float3 cameraY;
    float3 cameraZ;

    float2 cameraAspect;
    void updateCameraAspect() {
        cameraAspect.y = tanf((fovY * 0.5f) * DEGREE);
        cameraAspect.x = cameraAspect.y * screenWidth / screenHeight;
    }

    bool changed = false;

public:
    const float2& getCameraAspect() const { return cameraAspect; }
    const float3& getCameraPos() const { return cameraPos; }
    const float3& getCameraX() const { return cameraX; }
    const float3& getCameraY() const { return cameraY; }
    const float3& getCameraZ() const { return cameraZ; }
    const float getScreenWidth() const { return screenWidth; }
    const float getScreenHeight() const { return screenHeight; }
    const float getFovY() const { return fovY; }

    void setCameraPos(const float3& pos) { cameraPos = pos; changed = true; }
    void setCameraX(const float3& xDir) { cameraX = xDir; changed = true; }
    void setCameraY(const float3& yDir) { cameraY = yDir; changed = true; }
    void setCameraZ(const float3& zDir) { cameraZ = zDir; changed = true; }
    void setScreenSize(float w, float h) {
        screenWidth = w;
        screenHeight = h;
        updateCameraAspect();
        changed = true;
    }
    void setFovY(float fovY) {
        this->fovY = fovY;
        updateCameraAspect();
        changed = true;
    }

    bool notifyChanged() {
        if (changed) {
            changed = false;
            return true;
        }
        return false;
    }

    virtual void update(const InputEngine& input) {}
};


class FpsCamera : public PinholeCamera
{
    float pitch = 0.0f;      // Vertical rotation (up/down)
    float yaw = 0.0f;        // Horizontal rotation (left/right)

    float moveSpeed = 5.0f;
    float mouseSensitivity = 0.003f;

    void updateCameraOrientation();

public:
    float getMoveSpeed() const { return moveSpeed; }
    float getMouseSensitivity() const { return mouseSensitivity; }

    void setMoveSpeed(float speed) { moveSpeed = speed; }
    void setMouseSensitivity(float sensitivity) { mouseSensitivity = sensitivity; }

    void initFps(const float3& position, float initialYaw = 0.0f, float initialPitch = 0.0f);
    void rotate(float deltaPitch, float deltaYaw);
    void moveForward(float distance);
    void moveRight(float distance);
    void moveUp(float distance);

    virtual void update(const InputEngine& input);
};

// Implementation
inline void FpsCamera::updateCameraOrientation()
{
    // Clamp pitch to avoid gimbal lock
    if (pitch > 89.0f * DEGREE) pitch = 89.0f * DEGREE;
    if (pitch < -89.0f * DEGREE) pitch = -89.0f * DEGREE;

    // Calculate camera direction vectors
    float3 forward;
    forward.x = cosf(pitch) * sinf(yaw);
    forward.y = sinf(pitch);
    forward.z = -cosf(pitch) * cosf(yaw);
    forward = forward.normalize();

    float3 worldUp(0.0f, 1.0f, 0.0f);
    float3 right = float3::cross(forward, worldUp).normalize();
    float3 up = float3::cross(right, forward).normalize();

    setCameraZ(forward);
    setCameraX(right);
    setCameraY(up * -1.0f);       // Vulkan Y is down
}

inline void FpsCamera::initFps(const float3& position, float initialYaw, float initialPitch)
{
    setCameraPos(position);
    pitch = initialPitch;
    yaw = initialYaw;
    updateCameraOrientation();
}

inline void FpsCamera::rotate(float deltaPitch, float deltaYaw)
{
    pitch += deltaPitch;
    yaw += deltaYaw;
    updateCameraOrientation();
}

inline void FpsCamera::moveForward(float distance)
{
    float3 forward;
    forward.x = sinf(yaw);
    forward.y = 0.0f;  // Keep movement on horizontal plane
    forward.z = -cosf(yaw);
    forward = forward.normalize();

    setCameraPos(getCameraPos() + forward * distance);
}

inline void FpsCamera::moveRight(float distance)
{
    float3 right;
    right.x = cosf(yaw);
    right.y = 0.0f;
    right.z = sinf(yaw);
    right = right.normalize();

    setCameraPos(getCameraPos() + right * distance);
}

inline void FpsCamera::moveUp(float distance)
{
    setCameraPos(getCameraPos() + float3(0.0f, distance, 0.0f));
}

inline void FpsCamera::update(const InputEngine& input)
{
    // Mouse rotation with left button
    float2 mouseDelta = input.getMouseDragged(LButton);
    float deltaYaw = mouseDelta.x * mouseSensitivity;
    float deltaPitch = mouseDelta.y * mouseSensitivity;

    if (deltaYaw != 0.0f || deltaPitch != 0.0f) {
        rotate(-deltaPitch, deltaYaw);  // Negative pitch for natural mouse movement
    }

    // Keyboard movement
    float speed = moveSpeed * 0.016f;  // Approximate frame time (60 FPS)

    if (input.isKeyPressed('W') || input.isKeyPressed('w')) moveForward(speed);
    if (input.isKeyPressed('S') || input.isKeyPressed('s')) moveForward(-speed);
    if (input.isKeyPressed('D') || input.isKeyPressed('d')) moveRight(speed);
    if (input.isKeyPressed('A') || input.isKeyPressed('a')) moveRight(-speed);
    if (input.isKeyPressed(' ')) moveUp(speed);
    if (input.isKeyPressed('C') || input.isKeyPressed('c')) moveUp(-speed);
}

#endif