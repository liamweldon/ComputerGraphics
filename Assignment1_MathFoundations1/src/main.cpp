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
	Vector4f a(1.0f ,0.0f,  0.0f,   0.0f);
	Vector4f b(0.0f ,1.0f,  0.0f,   0.0f);
	Vector4f c(0.0f ,0.0f,  1.0f,   0.0f);
	Vector4f d(0.0f ,0.0f,  0.0f,   1.0f);
	Matrix4f myIdentity(a,b,c,d);

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
// TODO: Test against glm::scale
bool unitTest3(){
	glm::mat4 glmScale = glm::mat4(2.0f);
	Vector4f a(1.0f,0,0,0);
	Vector4f b(0.0f,1.0f,0,0);
	Vector4f c(0,0,1.0f,0);
	Vector4f d(0,0,0,1.0f);
	Matrix4f myScaled(a,b,c,d);
    myScaled.MakeScale(2.0f,2.0f,2.0f);
/*
    std::cout << ", " + std::to_string(myScaled[0][0]) + ", " + std::to_string(myScaled[0][1]) + ", " + std::to_string(myScaled[0][2]) + ", " + std::to_string(myScaled[0][3]) << "\n";
    std::cout << ", " + std::to_string(myScaled[1][0]) + ", " + std::to_string(myScaled[1][1]) + ", " + std::to_string(myScaled[1][2]) + ", " + std::to_string(myScaled[1][3]) << "\n";
    std::cout << ", " + std::to_string(myScaled[2][0]) + ", " + std::to_string(myScaled[2][1]) + ", " + std::to_string(myScaled[2][2]) + ", " + std::to_string(myScaled[2][3]) << "\n";
    std::cout << ", " + std::to_string(myScaled[3][0]) + ", " + std::to_string(myScaled[3][1]) + ", " + std::to_string(myScaled[3][2]) + ", " + std::to_string(myScaled[3][3]) << "\n";
*/
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
        glmScale[3][2]==myScaled[3][2] ){
            return true;
    }
    // && glmScale[3][3] == myScaled[3][3]
    myScaled.print(myScaled);
	
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
     std::cout << "" + to_string(col0[0]) + ", " + to_string(col0[1]) + ", " + to_string(col0[2]) + ", " + to_string(col0[3]);
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

    Matrix4f c = a.times(b);

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

int main(){
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0: " << unitTest0() << " \n";
    std::cout << "Passed 1: " << unitTest1() << " \n";
    std::cout << "Passed 2: " << unitTest2() << " \n";
    std::cout << "Passed 3: " << unitTest3() << " \n";
    std::cout << "Passed 4: " << unitTest4() << " \n";
    std::cout << "Passed 5: " << unitTest5() << " \n";
    std::cout << "Passed 6: " << unitTest6() << " \n";
    std::cout << "Passed 7: " << unitTest7() << " \n";
    std::cout << "Passed 8: " << unitTest8() << " \n";
    std::cout << "Passed 9: " << unitTest9() << " \n";

    return 0;
}
