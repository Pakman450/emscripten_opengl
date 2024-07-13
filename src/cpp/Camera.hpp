#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
    public:

        // The final matrix required for creating a view matrix.
        glm::mat4 GetViewMatrix() const;

        void MouseLook(int mouseX, int mouseY);
        void MoveFoward(float);
        void MoveBackward(float);
        void MoveLeft(float);
        void MoveRight(float);
        Camera();
    private:
        glm::vec3 mEye;
        glm::vec3 mViewDirection;
        glm::vec3 mUpVector;
        glm::vec2 mOldMousePosition;



};



#endif