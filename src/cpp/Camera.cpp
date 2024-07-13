#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/rotate_vector.hpp>

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
    return glm::lookAt(mEye,mEye+mViewDirection,mUpVector);
}
void Camera::MouseLook(int mouseX,int mouseY){
    std::cout <<"mouseX " << mouseX << "mouseY " << mouseY << std::endl;

    static bool firstLook = true;
    glm::vec2 currentMouse = glm::vec2(mouseX,mouseY);      
    if(firstLook){
        mOldMousePosition=currentMouse;
        firstLook=false;
    }
    
    glm::vec2 mouseDelta = mOldMousePosition - currentMouse; 


    mViewDirection = glm::rotate(mViewDirection, glm::radians((float) mouseDelta.x) ,mUpVector );
    mOldMousePosition = currentMouse;
}
void Camera::MoveFoward(float speed){
    // Simple, but not yet correct!
    mEye += (mViewDirection*speed);
};
void Camera::MoveBackward(float speed){
    mEye -= (mViewDirection*speed);
};
void Camera::MoveLeft(float speed){
    glm::vec3 rightVector = glm::cross(mViewDirection, mUpVector);
    mEye -= rightVector*speed;
};
void Camera::MoveRight(float speed){
    glm::vec3 rightVector = glm::cross(mViewDirection, mUpVector);
    mEye += rightVector*speed;
    };
        