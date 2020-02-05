// High level design note
// Our matrix should match the behavior of the glm library.
#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <cmath>
#include <iostream>
#include <string>

// We need to Vector4f header in order to multiply a matrix
// by a vector.
#include "Vector4f.h"


using namespace std;

// Matrix 4f represents 4x4 matrices in Math
struct Matrix4f{
private:
    float n[4][4];  // Store each value of the matrix

public:
    Matrix4f() = default;

    // TODO: Row or column major order you decide!
    // Matrix constructor with 9 scalar values.
    Matrix4f( float n00, float n01, float n02, float n03,
              float n10, float n11, float n12, float n13,
              float n20, float n21, float n22, float n23,
              float n30, float n31, float n32, float n33){

        n[0][0] = n00; n[1][0] = n10; n[2][0] = n20; n[3][0] = n30;
        n[0][1] = n01; n[1][1] = n11; n[2][1] = n21; n[3][1] = n31;
        n[0][2] = n02; n[1][2] = n12; n[2][2] = n22; n[3][2] = n32;
        n[0][3] = n03; n[1][3] = n13; n[2][3] = n23; n[3][3] = n33;
    }

    // Matrix constructor from four vectors.
    // Note: 'd' will almost always be 0,0,0,1
    Matrix4f(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d){
      n[0][0] = a.x; n[0][1] = b.x; n[0][2] = c.x; n[0][3] = d.x;
      n[1][0] = a.y; n[1][1] = b.y; n[1][2] = c.y; n[1][3] = d.y;
      n[2][0] = a.z; n[2][1] = b.z; n[2][2] = c.z; n[2][3] = d.z;
      n[3][0] = a.w; n[3][1] = b.w; n[3][2] = c.w; n[3][3] = d.w;
    }

    // Makes the matrix an identity matrix
    void identity(){
        n[0][0] = 1; n[0][1] = 0; n[0][2] = 0; n[0][3] = 0;
        n[1][0] = 0; n[1][1] = 1; n[1][2] = 0; n[1][3] = 0;
        n[2][0] = 0; n[2][1] = 0; n[2][2] = 1; n[2][3] = 0;
        n[3][0] = 0; n[3][1] = 0; n[3][2] = 0; n[3][3] = 1;
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j){
      return (n[j][i]);
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const{
      return (n[j][i]);
    }

    // Return a single row vector from the matrix
    Vector4f& operator [](int j){
      return (*reinterpret_cast<Vector4f *>(n[j]));
    }

    // Return a single row vector from the matrix
    const Vector4f& operator [](int j) const{
      return (*reinterpret_cast<const Vector4f *>(n[j]));
    }

    Vector4f& column(int j) {
        float col[4];
        col[0] = n[0][j];
        col[1] = n[1][j];
        col[2] = n[2][j];
        col[3] = n[3][j];
        Vector4f vec = Vector4f(col);
        return Vector4f(col);
    }

    const Vector4f& column(int j) const {
        float col[4];
        col[0] = n[j][0];
        col[1] = n[j][1];
        col[2] = n[j][2];
        col[3] = n[j][3];
        const Vector4f rv = Vector4f(col);
        return rv;
    }

    // Make a matrix rotate about various axis
    Matrix4f MakeRotationX(float t){
        Matrix4f rotationMatrix =
            Matrix4f(
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, cos(t), -sin(t), 0.0f,
                0.0f, sin(t), cos(t), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        *this = this->times(rotationMatrix);
        return(*this); // You will need to modify this.
                                        // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeRotationY(float t){
        Matrix4f rotationMatrix =
            Matrix4f(
                cos(t), 0.0f, sin(t), 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                -sin(t), 0.0f, cos(t), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        *this = this->times(rotationMatrix);
        return(*this);

                            // You will need to modify this.
                            // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeRotationZ(float t){
        Matrix4f rotationMatrix =
            Matrix4f(
                cos(t), -sin(t), 0.0f, 0.0f,
                sin(t), cos(t), 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        *this = this->times(rotationMatrix);
        return(*this);
                            // You will need to modify this.
                            // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeScale(float sx,float sy, float sz){
        Matrix4f scaleMatrix =
            Matrix4f(
                sx, 0.0f, 0.0f, 0.0f,
                0.0f, sy, 0.0f, 0.0f,
                0.0f, 0.0f, sz, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        *this = this->times(scaleMatrix);
        return(*this);
                            // You will need to modify this.
                            // When you test, test against glm_gtx_transform
    }

    Matrix4f times(const Matrix4f& B) const{
        const Matrix4f& A = *this;
        float arr[4][4];
        arr[0][0] = Dot(A[0], Vector4f(B.column(0))); arr[0][1] = Dot(A[0], Vector4f(B.column(1))); arr[0][2] = Dot(A[0], Vector4f(B.column(2))); arr[0][3] = Dot(A[0], Vector4f(B.column(3)));
        arr[1][0] = Dot(A[1], Vector4f(B.column(0))); arr[1][1] = Dot(A[1], Vector4f(B.column(1))); arr[1][2] = Dot(A[1], Vector4f(B.column(2))); arr[1][3] = Dot(A[1], Vector4f(B.column(3)));
        arr[2][0] = Dot(A[2], Vector4f(B.column(0))); arr[2][1] = Dot(A[2], Vector4f(B.column(1))); arr[2][2] = Dot(A[2], Vector4f(B.column(2))); arr[2][3] = Dot(A[2], Vector4f(B.column(3)));
        arr[3][0] = Dot(A[3], Vector4f(B.column(0))); arr[3][1] = Dot(A[3], Vector4f(B.column(1))); arr[3][2] = Dot(A[3], Vector4f(B.column(2))); arr[3][3] = Dot(A[3], Vector4f(B.column(3)));

        Matrix4f mat4 = 
   Matrix4f(arr[0][0], arr[0][1], arr[0][2], arr[0][3],
            arr[1][0], arr[1][1], arr[1][2], arr[1][3],
            arr[2][0], arr[2][1], arr[2][2], arr[2][3],
            arr[3][0], arr[3][1], arr[3][2], arr[3][3]);
        //this->print(mat4);
        return mat4;
    }

    void print(Matrix4f& myScaled) const{
        std::cout << ", " + std::to_string(myScaled[0][0]) + ", " + std::to_string(myScaled[1][0]) + ", " + std::to_string(myScaled[2][0]) + ", " + std::to_string(myScaled[3][0]) << "\n";
        std::cout << ", " + std::to_string(myScaled[0][1]) + ", " + std::to_string(myScaled[1][1]) + ", " + std::to_string(myScaled[2][1]) + ", " + std::to_string(myScaled[3][1]) << "\n";
        std::cout << ", " + std::to_string(myScaled[0][2]) + ", " + std::to_string(myScaled[1][2]) + ", " + std::to_string(myScaled[2][2]) + ", " + std::to_string(myScaled[3][2]) << "\n";
        std::cout << ", " + std::to_string(myScaled[0][3]) + ", " + std::to_string(myScaled[1][3]) + ", " + std::to_string(myScaled[2][3]) + ", " + std::to_string(myScaled[3][3]) << "\n";
    }
};

// Matrix Multiplication
Matrix4f operator *(const Matrix4f& A, const Matrix4f& B){

    Matrix4f mat4 = A.times(B);
    return mat4;
}

// Matrix multiply by a vector

Vector4f operator *(const Matrix4f& M, const Vector4f& v){
  Vector4f vec = Vector4f(Dot(M[0], v), Dot(M[1], v), Dot(M[2], v), Dot(M[3], v));
  return vec;
}

#endif
