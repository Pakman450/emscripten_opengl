#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(){

    // we are the origin.
    mEye             = glm::vec3(0.f,0.f,0.f);

    // looking towards the negatice Z direciton
    mViewDirection = glm::vec3(0.f,0.f,-1.f);
    // Assume we are at a perfect plane thinking that hte Z and X plane is the ground
    mUpVector        = glm::vec3(0.f,1.f,0.f);
}


// The final matrix required for creating a view matrix.
glm::mat4 Camera::GetViewMatrix() const{
    return glm::lookAt(mEye,mViewDirection,mUpVector);
}
void Camera::MouseLook(int mouseX,int mouseY){
    glm::rotate();
    mOldMousePosition
    std::cout <<"mouseX " << mouseX << "mouseY " << mouseY << std::endl;
}
void Camera::MoveFoward(float speed){
    // Simple, but not yet correct!
    mEye.z -= speed;
};
void Camera::MoveBackward(float speed){
    mEye.z += speed;
};
void Camera::MoveLeft(float speed){
    mEye.x += speed;
};
void Camera::MoveRight(float speed){
    mEye.x -= speed;
};
        