// Includes for the assignment
#include "Vector4f.h"
#include "Matrix4f.h"
#include <iostream>
#include <string>


// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

bool compareMatrices(Matrix4f mines, glm::mat4 theirs) {
    float floatCompArr[16] = {
            mines[0][0] - theirs[0][0],
            mines[0][1] - theirs[0][1],
            mines[0][2] - theirs[0][2],
            mines[0][3] - theirs[0][3],
            mines[1][0] - theirs[1][0],
            mines[1][1] - theirs[1][1],
            mines[1][2] - theirs[1][2],
            mines[1][3] - theirs[1][3],
            mines[2][0] - theirs[2][0],
            mines[2][1] - theirs[2][1],
            mines[2][2] - theirs[2][2],
            mines[2][3] - theirs[2][3],
            mines[3][0] - theirs[3][0],
            mines[3][1] - theirs[3][1],
            mines[3][2] - theirs[3][2],
            mines[3][3] - theirs[3][3] };
        if (floatCompArr[0] < .01 && floatCompArr[0] > -.01 &&
            floatCompArr[1] < .01 && floatCompArr[1] > -.01 &&
            floatCompArr[2] < .01 && floatCompArr[2] > -.01 &&
            floatCompArr[3] < .01 && floatCompArr[3] > -.01 &&
            floatCompArr[4] < .01 && floatCompArr[4] > -.01 &&
            floatCompArr[5] < .01 && floatCompArr[5] > -.01 &&
            floatCompArr[6] < .01 && floatCompArr[6] > -.01 &&
            floatCompArr[7] < .01 && floatCompArr[7] > -.01 &&
            floatCompArr[8] < .01 && floatCompArr[8] > -.01 &&
            floatCompArr[9] < .01 && floatCompArr[9] > -.01 &&
            floatCompArr[10] < .01 && floatCompArr[10] > -.01 &&
            floatCompArr[11] < .01 && floatCompArr[11] > -.01 &&
            floatCompArr[12] < .01 && floatCompArr[12] > -.01 &&
            floatCompArr[13] < .01 && floatCompArr[13] > -.01 &&
            floatCompArr[14] < .01 && floatCompArr[14] > -.01 &&
            floatCompArr[15] < .01 && floatCompArr[15] > -.01
            ) {
            return true;
        }
        glm::mat4 myScaled = theirs;
        mines.print(mines);
        std::cout << "\n\n";
        std::cout << ", " + std::to_string(myScaled[0][0]) + ", " + std::to_string(myScaled[1][0]) + ", " + std::to_string(myScaled[2][0]) + ", " + std::to_string(myScaled[3][0]) << "\n";
        std::cout << ", " + std::to_string(myScaled[0][1]) + ", " + std::to_string(myScaled[1][1]) + ", " + std::to_string(myScaled[2][1]) + ", " + std::to_string(myScaled[3][1]) << "\n";
        std::cout << ", " + std::to_string(myScaled[0][2]) + ", " + std::to_string(myScaled[1][2]) + ", " + std::to_string(myScaled[2][2]) + ", " + std::to_string(myScaled[3][2]) << "\n";
        std::cout << ", " + std::to_string(myScaled[0][3]) + ", " + std::to_string(myScaled[1][3]) + ", " + std::to_string(myScaled[2][3]) + ", " + std::to_string(myScaled[3][3]) << "\n";
        return false;
}

bool compareVecs(Vector4f a, Vector4f b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

// Sample unit test comparing against GLM.
bool unitTest0(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
	
    return false;	
}

bool unitTest1(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity(0,0) &&
        glmIdentityMatrix[0][1]==myIdentity(0,1) &&
        glmIdentityMatrix[0][2]==myIdentity(0,2) &&
        glmIdentityMatrix[0][3]==myIdentity(0,3) &&
        glmIdentityMatrix[1][0]==myIdentity(1,0) &&
        glmIdentityMatrix[1][1]==myIdentity(1,1) &&
        glmIdentityMatrix[1][2]==myIdentity(1,2) &&
        glmIdentityMatrix[1][3]==myIdentity(1,3) &&
        glmIdentityMatrix[2][0]==myIdentity(2,0) &&
        glmIdentityMatrix[2][1]==myIdentity(2,1) &&
        glmIdentityMatrix[2][2]==myIdentity(2,2) &&
        glmIdentityMatrix[2][3]==myIdentity(2,3) &&
        glmIdentityMatrix[3][0]==myIdentity(3,0) &&
        glmIdentityMatrix[3][1]==myIdentity(3,1) &&
        glmIdentityMatrix[3][2]==myIdentity(3,2) &&
        glmIdentityMatrix[3][3]==myIdentity(3,3)){
            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
bool unitTest2(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
    
    Matrix4f myIdentity = Matrix4f();
    myIdentity.identity();

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
bool unitTest3(){
	glm::mat4 glmScale = glm::mat4(1.0f);
    glm::vec3 scaleVec = glm::vec3(2, 2, 2);
    glmScale = glm::scale(glmScale, scaleVec);

	Vector4f a(1.0f,0,0,0);
	Vector4f b(0.0f,1.0f,0,0);
	Vector4f c(0,0,1.0f,0);
	Vector4f d(0,0,0,1.0f);
	Matrix4f myScaled(a,b,c,d);
    myScaled.MakeScale(2.0f,2.0f,2.0f);

    if(
        glmScale[0][0]==myScaled[0][0] &&
        glmScale[0][1]==myScaled[0][1] &&
        glmScale[0][2]==myScaled[0][2] &&
        glmScale[0][3]==myScaled[0][3] &&
        glmScale[1][0]==myScaled[1][0] &&
        glmScale[1][1]==myScaled[1][1] &&
        glmScale[1][2]==myScaled[1][2] &&
        glmScale[1][3]==myScaled[1][3] &&
        glmScale[2][0]==myScaled[2][0] &&
        glmScale[2][1]==myScaled[2][1] &&
        glmScale[2][2]==myScaled[2][2] &&
        glmScale[2][3]==myScaled[2][3] &&
        glmScale[3][0]==myScaled[3][0] &&
        glmScale[3][1]==myScaled[3][1] &&
        glmScale[3][2]==myScaled[3][2] &&
        glmScale[3][3]==myScaled[3][3]){

            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
// Testing operator
bool unitTest4(){
	glm::mat4 glmTest = glm::mat4(1.0f);
    glmTest[1][3] = 72.0f;
    glmTest[2][3] = 2.1f;

	Matrix4f myMatrix(0,0,0,0,
                      0,0,0,0,
                      0,0,0,0,
                      0,0,0,0);

    myMatrix[1][3] = 72.0f;
    myMatrix[2][3] = 2.1f;

    if( glmTest[1][3]==myMatrix[1][3] &&
        glmTest[2][3]==myMatrix[2][3] ){
            return true;
    }
	
    return false;	
}

// Sample unit test testing your library
bool unitTest5(){
  Vector4f a(1,1,1,1);
  Vector4f b(0,0,0,0);
  Vector4f c = a + b;

  if(c.x == 1 && c.y == 1 && c.z ==1 && c.w==1){
    return true;
  }
    return false;
}


bool unitTest6() {
    Vector4f a(1, 2, 3, 4);
    Vector4f b(2, 3, 4, 5);
    
    float c = Dot(a, b);
    if (c > 39.99 && c < 40.01) {
        return true;
    }
    return false;
}

bool unitTest7() {
    Matrix4f a(
        1, 2, 3, 9,
        0, 0, 0, 0,
        4, 2, 7, 1,
        5, 2, 1, 3);
    Vector4f row0 = a.row(0);
    Vector4f col0 = a[0];

    if (row0[0] == 1 &&
        row0[1] == 2 &&
        row0[2] == 3 &&
        row0[3] == 9 &&
        col0[0] == 1 &&
        col0[1] == 0 &&
        col0[2] == 4 &&
        col0[3] == 5) {
        return true;
    }
    a.print(a);
     return false;
}


bool unitTest8() {
    Matrix4f a(
        1, 2, 3, 9,
        0, 0, 0, 0,
        4, 2, 7, 1,
        5, 2, 1, 3);

    Matrix4f b(
        1, 1, 3, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1);

    Matrix4f c = a * b;

    Matrix4f test(
        15, 15, 17, 15,
        0, 0, 0, 0,
        14, 14, 22, 14,
        11, 11, 21, 11
    );

    float floatCompArr[16] = {
            test[0][0] - c[0][0],
            test[0][1] - c[0][1],
            test[0][2] - c[0][2],
            test[0][3] - c[0][3],
            test[1][0] - c[1][0],
            test[1][1] - c[1][1],
            test[1][2] - c[1][2],
            test[1][3] - c[1][3],
            test[2][0] - c[2][0],
            test[2][1] - c[2][1],
            test[2][2] - c[2][2],
            test[2][3] - c[2][3],
            test[3][0] - c[3][0],
            test[3][1] - c[3][1],
            test[3][2] - c[3][2],
            test[3][3] - c[3][3] };
        if (floatCompArr[0] < .01 && floatCompArr[0] > -.01 &&
            floatCompArr[1] < .01 && floatCompArr[1] > -.01 &&
            floatCompArr[2] < .01 && floatCompArr[2] > -.01 &&
            floatCompArr[3] < .01 && floatCompArr[3] > -.01 &&
            floatCompArr[4] < .01 && floatCompArr[4] > -.01 &&
            floatCompArr[5] < .01 && floatCompArr[5] > -.01 &&
            floatCompArr[6] < .01 && floatCompArr[6] > -.01 &&
            floatCompArr[7] < .01 && floatCompArr[7] > -.01 &&
            floatCompArr[8] < .01 && floatCompArr[8] > -.01 &&
            floatCompArr[9] < .01 && floatCompArr[9] > -.01 &&
            floatCompArr[10] < .01 && floatCompArr[10] > -.01 &&
            floatCompArr[11] < .01 && floatCompArr[11] > -.01 &&
            floatCompArr[12] < .01 && floatCompArr[12] > -.01 &&
            floatCompArr[13] < .01 && floatCompArr[13] > -.01 &&
            floatCompArr[14] < .01 && floatCompArr[14] > -.01 &&
            floatCompArr[15] < .01 && floatCompArr[15] > -.01
            ) {
            return true;
        }
        return false;

}

bool unitTest9() {
    Matrix4f a(
        1, 2, 3, 9,
        0, 0, 0, 0,
        4, 2, 7, 1,
        5, 2, 1, 3);

    Matrix4f b(
        1, 1, 3, 1,
        5, 1, 1, 1,
        4, 1, 1, 1,
        7, 1, 1, 1);


    float dot = Dot(Vector4f(a.row(0)), b[0]);
    
    if (dot < 86.01 && dot > 85.99) {
        return true;
    }
    cout << to_string(dot) + "\n";
    return false;
}
// trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

bool unitTest10() {

    glm::mat4 glmRotate = glm::rotate(glm::radians(67.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Matrix4f myRotate = Matrix4f();
    myRotate.MakeRotationX(glm::radians(67.0f));

    return compareMatrices(myRotate, glmRotate);
}

bool unitTest11() {
    glm::mat4 glmRotate = glm::rotate(glm::radians(67.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Matrix4f myRotate = Matrix4f();
    myRotate.MakeRotationY(glm::radians(67.0f));

    return compareMatrices(myRotate, glmRotate);
}

bool unitTest12() {
    glm::mat4 glmRotate = glm::rotate(glm::radians(67.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    Matrix4f myRotate = Matrix4f();
    myRotate.MakeRotationZ(glm::radians(67.0f));

    return compareMatrices(myRotate, glmRotate);
}

bool unitTest13() {
    Vector4f vec = Vector4f(2.0f, 3.0f, 4.0f, 5.0f);
    Matrix4f mat = Matrix4f(
        1, 2, 3, 9,
        0, 0, 0, 0,
        4, 2, 7, 1,
        5, 2, 1, 3);

    Vector4f test = Vector4f(65.0f, 0.0f, 47.0f, 35.0f);

    Vector4f multVec = mat * vec;
    return (test[0] == multVec[0] &&
        test[1] == multVec[1] &&
        test[2] == multVec[2] &&
        test[3] == multVec[3]);
}

bool unitTest14() {
    Vector4f a = Vector4f(2.0f, 3.0f, 4.0f, 5.0f);
    Vector4f b = Vector4f(10.0f, 5.0f, 0.0f, 5.0f);
    Vector4f mult = a * 3;
    b *= 4;
    Vector4f testA = Vector4f(6.0f, 9.0f, 12.0f, 15.0f);
    Vector4f testB = Vector4f(40.0f, 20.0f, 0.0f, 20.0f);


    return (compareVecs(mult, testA) && compareVecs(b, testB));

}

bool unitTest15() {
    Vector4f a = Vector4f(2.0f, 3.0f, 4.0f, 5.0f);
    Vector4f b = Vector4f(10.0f, 5.0f, 0.0f, 5.0f);
    Vector4f div = a / 2;
    b /= 5;
    Vector4f testA = Vector4f(1.0f, 1.5f, 2.0f, 2.5f);
    Vector4f testB = Vector4f(2.0f, 1.0f, 0.0f, 1.0f);

    return (compareVecs(div, testA) && compareVecs(b, testB));

}

bool unitTest16() {
    Vector4f a = Vector4f(2.0f, 3.0f, 4.0f, 5.0f);
    Vector4f b = Vector4f(10.0f, 5.0f, 0.0f, 5.0f);
    Vector4f plus = a + b;
    b += a;
    Vector4f test = Vector4f(12.0f, 8.0f, 4.0f, 10.0f);

    return (compareVecs(plus, test) && compareVecs(b, test));
}

bool unitTest17() {
    Vector4f a = Vector4f(2.0f, 3.0f, 4.0f, 5.0f);
    Vector4f negate = -a;
    Vector4f test = Vector4f(-2.0f, -3.0f, -4.0f, -5.0f);

    return compareVecs(negate, test);

}

bool unitTest18() {
    Vector4f a = Vector4f(2.0f, 3.0f, 4.0f, 5.0f);
    Vector4f b = Vector4f(10.0f, 5.0f, 0.0f, 5.0f);
    Vector4f minus = a - b;
    b -= a;

    Vector4f testA = Vector4f(-8.0f, -2.0f, 4.0f, 0.0f);
    Vector4f testB = Vector4f(8.0f, 2.0f, -4.0f, 0.0f);

    return (compareVecs(minus, testA) && compareVecs(b, testB));
}

bool unitTest19() {
    Vector4f a = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
    Vector4f normal = Normalize(a);
    
    Vector4f test = Vector4f(0.5f, 0.5f, 0.5f, 0.5f);
    return compareVecs(test, normal);
}

bool unitTest20() {
    Vector4f x = Vector4f(2.0f, 0.0f, 0.0f, 1.0f);
    Vector4f z = Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

    Vector4f y = Vector4f(0.0f, -2.0f, 0.0f, 1.0f);
    Vector4f cross = CrossProduct(x, z);
    return compareVecs(cross, y);
}

bool unitTest21() {
    Vector4f a = Vector4f(2.0f, 1.0f, 1.0f, 0.0f);
    Vector4f b = Vector4f(2.0f, 2.0f, 2.0f, 2.0f);

    Vector4f project = Project(a, b);

    Vector4f test = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);

    return compareVecs(project, test);

}

bool unitTest22() {
    Vector4f a = Vector4f(2.0f, sqrt(2.0f), 1.0f, 3.0f);
    float four = 4.0f;
    float mag = Magnitude(a);

    return mag == four;
}

int main(){
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0:  " << unitTest0() << " \n";
    std::cout << "Passed 1:  " << unitTest1() << " \n";
    std::cout << "Passed 2:  " << unitTest2() << " \n";
    std::cout << "Passed 3:  " << unitTest3() << " \n";
    std::cout << "Passed 4:  " << unitTest4() << " \n";
    std::cout << "Passed 5:  " << unitTest5() << " \n";
    std::cout << "Passed 6:  " << unitTest6() << " \n";
    std::cout << "Passed 7:  " << unitTest7() << " \n";
    std::cout << "Passed 8:  " << unitTest8() << " \n";
    std::cout << "Passed 9:  " << unitTest9() << " \n";
    std::cout << "Passed 10: " << unitTest10() << " \n";
    std::cout << "Passed 11: " << unitTest11() << " \n";
    std::cout << "Passed 12: " << unitTest12() << " \n";
    std::cout << "Passed 13: " << unitTest13() << " \n";
    std::cout << "Passed 14: " << unitTest14() << " \n";
    std::cout << "Passed 15: " << unitTest15() << " \n";
    std::cout << "Passed 16: " << unitTest16() << " \n";
    std::cout << "Passed 17: " << unitTest17() << " \n";
    std::cout << "Passed 18: " << unitTest18() << " \n";
    std::cout << "Passed 19: " << unitTest19() << " \n";
    std::cout << "Passed 20: " << unitTest20() << " \n";
    std::cout << "Passed 21: " << unitTest21() << " \n";
    std::cout << "Passed 22: " << unitTest22() << " \n";




    return 0;
}