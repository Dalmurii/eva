#ifndef INPUT_H
#define INPUT_H

#include "math_types.h"

enum MouseButton
{
    LButton = 0,
    MButton = 1,
    RButton = 2,
    numButtons = 3
};

class InputEngine
{
    // Keyboard state
    bool keys[512] = {false};

    // Mouse position (previous frame state pattern)
    float2 mousePos;
    float2 mousePosPrev;

    // Mouse button state
    bool mouseButton[numButtons] = {false};
    bool mouseButtonPrev[numButtons] = {false};

public:
    // Key state queries
    bool isKeyPressed(int key) const {
        if (key < 0 || key >= 512) return false;
        return keys[key];
    }

    // Mouse state queries
    bool isMouseButtonPressed(MouseButton button) const {
        return mouseButton[button];
    }

    bool isMouseButtonJustPressed(MouseButton button) const {
        return !mouseButtonPrev[button] && mouseButton[button];
    }

    bool isMouseButtonJustReleased(MouseButton button) const {
        return mouseButtonPrev[button] && !mouseButton[button];
    }

    float2 getMousePos() const { return mousePos; }

    // Get mouse delta while button is held down
    float2 getMouseDragged(MouseButton button) const {
        if (mouseButtonPrev[button] && mouseButton[button])
            return float2(mousePos.x - mousePosPrev.x, mousePos.y - mousePosPrev.y);
        return float2(0.0f, 0.0f);
    }

    // Update methods (called from callbacks)
    void onKey(int key, int action, int mods) {
        if (key >= 0 && key < 512) {
            keys[key] = (action == 1 || action == 2);  // 1=press, 2=repeat
        }
    }

    void onMouseButton(int button, int action, double xpos, double ypos) {
        if (button >= 0 && button < numButtons) {
            mouseButton[button] = (action == 1);  // 1=press
        }
    }

    void onCursorPos(double xpos, double ypos) {
        mousePos.x = (float)xpos;
        mousePos.y = (float)ypos;
    }

    void onScroll(double xoffset, double yoffset) {
        // Can be used for zoom or other features
    }

    // Call once per frame to update previous state
    void update() {
        mousePosPrev = mousePos;
        for (int i = 0; i < numButtons; ++i) {
            mouseButtonPrev[i] = mouseButton[i];
        }
    }
};

#endif