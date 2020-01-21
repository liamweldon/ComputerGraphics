/** @file main.cpp
 *  @brief Entry point into our program.
 *  
 *  Welcome to the Great Looking Software Render 
 *  code base (Yes, I needed something with a gl prefix).
 *
 *  This is where you will implement your graphics API.
 *
 *  Compile on the terminal with: 
 *
 *  clang++ -std=c++11 main.cpp -o main
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

// Load our libraries
#include <iostream>

// Some define values
#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 320

// C++ Standard Libraries
#include <iostream>

// User libraries
#include "GL.h"
#include "Color.h"
#include "TGA.h"
#include "Maths.h"

// Create a canvas to draw on.
TGA canvas(WINDOW_WIDTH,WINDOW_HEIGHT);
int drawLineIncrementalFB(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c, int prevX, int prevY);
int drawLineIncrementalFT(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c, int prevX, int prevY);



int compareY(const void* a, const void* b)
{
    const Vec2* v0 = (Vec2*)a;
    const Vec2* v1 = (Vec2*)b;
    if (v0->y > v1->y)
        return 1;
    else if (v0->y < v1->y)
        return -1;
    return 0;
}

int compareX(const void* a, const void* b) 
{
    const Vec2* v0 = (Vec2*)a;
    const Vec2* v1 = (Vec2*)b;
    if (v0->x > v1->x)
        return 1;
    else if (v0->x < v1->x)
        return -1;
    return 0;
}


// Implementation of Bresenham's Line Algorithm
// The input to this algorithm is two points and a color
// This algorithm will then modify a canvas (i.e. image)
// filling in the appropriate colors.
void drawLine(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c){
    bool steep = false;
    if(std::abs(v0.x-v1.x)<std::abs(v0.y-v1.y)){
        // If the line is steep we want to transpose the image.
        std::swap(v0.x,v0.y);
        std::swap(v1.x,v1.y);
        steep = true;
    }
    if(v0.x>v1.x){  // make it left-to-right
        std::swap(v0.x, v1.x);
        std::swap(v0.y, v1.y);
    }
    for(int x = v0.x; x <= v1.x; ++x){
        float t = (x-v0.x)/(float)(v1.x-v0.x);
        int y = v0.y*(1.0f-t) + v1.y*t;
        if(steep){
            canvas.setPixelColor(y,x,c);
        }else{
            canvas.setPixelColor(x,y,c);
        }
    }
}

void drawFlatBottomTriangle(Vec2 top, Vec2 left, Vec2 right, TGA& image, ColorRGB c) {
    int rightX = top.x;
    int leftX = top.x;
    int y = top.y;
    // std::cout << "Left:" + std::to_string(leftX) + " Right:" + std::to_string(rightX) + " Y:" + std::to_string(y) + "\r\n";

    //could be either, flat bottom
    while (y <= left.y) {
        leftX = drawLineIncrementalFB(top, left, image, c, leftX, y);
        rightX = drawLineIncrementalFB(top, right, image, c, rightX, y);
        // std::cout << "Left:" + std::to_string(leftX) + " Right:" + std::to_string(rightX) + " Y:" + std::to_string(y) + "\r\n";
        for (int i = leftX; i < rightX; i++) {
            canvas.setPixelColor(i, y, c);
        }
        y++;
    }
    drawLine(left, right, image, c);
}

void drawFlatTopTriangle(Vec2 bottom, Vec2 left, Vec2 right, TGA& image, ColorRGB c) {
    int rightX = bottom.x;
    int leftX = bottom.x;
    int y = bottom.y;
    //std::cout << "Left:" + std::to_string(leftX) + " Right:" + std::to_string(rightX) + " Y:" + std::to_string(y) + "\r\n";

    while (y >= left.y) {
        leftX = drawLineIncrementalFT(bottom, left, image, c, leftX, y);
        rightX = drawLineIncrementalFT(bottom, right, image, c, rightX, y);
        //std::cout << "Left:" + std::to_string(leftX) + " Right:" + std::to_string(rightX) + " Y:" + std::to_string(y) + "\r\n";
        for (int i = leftX; i < rightX; i++) {
            canvas.setPixelColor(i, y, c);
        }
        y--;
    }
    drawLine(left, right, image, c);

}


int drawLineIncrementalFT(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c, int prevX, int prevY) {
    bool steep = false;
    bool swapped = false;

    if (v0.x > v1.x) {
        swapped = true;
    }

    if (std::abs(v0.x - v1.x) < std::abs(v0.y - v1.y)) {
        // If the line is steep we want to transpose the image.
        std::swap(v0.x, v0.y);
        std::swap(v1.x, v1.y);
        steep = true;
    }

    if (swapped) {
        if (steep) {
            for (int x = prevY; x >= v1.x; --x) {
                float t = (x - v1.x) / (float)(v0.x - v1.x);
                int y = v1.y * (1.0f - t) + v0.y * t;
                if (x < prevY) {
                    return y;
                }
                canvas.setPixelColor(y, x, c);
            }
        }
        else {
            for (int x = prevX; x >= v1.x; --x) {
                float t = (x - v1.x) / (float)(v0.x - v1.x);
                int y = v1.y * (1.0f - t) + v0.y * t;
                if (y < prevY) {
                    return x;
                }
                else {
                    canvas.setPixelColor(x, y, c);
                }
            }
        }
        
    }
    if (steep) {
        for (int x = prevY; x >= v1.x; --x) {
            float t = (x - v0.x) / (float)(v1.x - v0.x);
            int y = v0.y * (1.0f - t) + v1.y * t;
            if (x < prevY) {
                return y;
            }
            canvas.setPixelColor(y, x, c);
        }
    }
    else {
        for (int x = prevX; x <= v1.x; ++x) {
            float t = (x - v0.x) / (float)(v1.x - v0.x);
            int y = v0.y * (1.0f - t) + v1.y * t;
            if (y < prevY) {
                return x;
            }
            else {
                canvas.setPixelColor(x, y, c);
            }
        }
    }
    
}


//Start w/ prevX = top.x, prevY = top.Y
int drawLineIncrementalFB(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c, int prevX, int prevY) {
    bool steep = false;
    bool swapped = false;
    
    if (v0.x > v1.x) {
        swapped = true;
    }

    
    if (std::abs(v0.x - v1.x) < std::abs(v0.y - v1.y)) {
        // If the line is steep we want to transpose the image.
        std::swap(v0.x, v0.y);
        std::swap(v1.x, v1.y);
        steep = true;
    }

    if (swapped) {
        if (steep) {
            for (int x = prevY; x >= v1.x; --x) {
                float t = (x - v1.x) / (float)(v0.x - v1.x);
                int y = v1.y * (1.0f - t) + v0.y * t;
                if (x > prevY) {
                    return y;
                }

                canvas.setPixelColor(y, x, c);
            }
        }
        else {
            for (int x = prevX; x >= v1.x; --x) {
                float t = (x - v1.x) / (float)(v0.x - v1.x);
                int y = v1.y * (1.0f - t) + v0.y * t;
                if (y > prevY) {
                    return x;
                }
                else {
                    canvas.setPixelColor(x, y, c);
                }
            }
        }
        
    }
    if (steep) {
        for (int x = prevY; x <= v1.x; ++x) {
            float t = (x - v0.x) / (float)(v1.x - v0.x);
            int y = v0.y * (1.0f - t) + v1.y * t;
            if (x > prevY) {
                return y;
            }
            canvas.setPixelColor(y, x, c);
        }
    }
    else {
        for (int x = prevX; x <= v1.x; ++x) {
            float t = (x - v0.x) / (float)(v1.x - v0.x);
            int y = v0.y * (1.0f - t) + v1.y * t;
            if (y > prevY) {
                return x;
            }
            else {
                canvas.setPixelColor(x, y, c);
            }
        }
    }
    
}

// Draw a triangle
void triangle(Vec2 v0, Vec2 v1, Vec2 v2,TGA& image, ColorRGB c){
    if(glFillMode==LINE){
        drawLine(v0,v1,image,c);
        drawLine(v1,v2,image,c);
        drawLine(v2,v0,image,c);
    }
    // TODO: Draw a filled triangle
    else if (glFillMode == FILL) {
        Vec2 sorted[3] = { v0, v1, v2 };
        qsort(sorted, 3, sizeof(Vec2), compareY);
        if (sorted[0].y == sorted[1].y) {
            sorted[0].x > sorted[1].x ?
                drawFlatTopTriangle(sorted[2], sorted[1], sorted[0], image, c) : drawFlatTopTriangle(sorted[2], sorted[0], sorted[1], image, c);
        }
        else if (sorted[1].y == sorted[2].y) {
            sorted[1].x > sorted[2].x ?
                drawFlatBottomTriangle(sorted[0], sorted[2], sorted[1], image, c) : drawFlatBottomTriangle(sorted[0], sorted[1], sorted[2], image, c);
        }
        else {
            Vec2 left, right;
            //TODO: fix for weird triangles
            int xIntercept = sorted[0].x + (int) ((float)(sorted[2].x - sorted[0].x) * ((float)(sorted[1].y - sorted[0].y) / (float)(sorted[2].y - sorted[0].y)));
            Vec2 intersect = Vec2(xIntercept, sorted[1].y);
            if (xIntercept < sorted[1].x) {
                drawFlatBottomTriangle(sorted[0], intersect, sorted[1], image, c);
                drawFlatTopTriangle(sorted[2], intersect, sorted[1], image, c);
            }
            else {
                drawFlatBottomTriangle(sorted[0], sorted[1], intersect, image, c);
                drawFlatTopTriangle(sorted[2], sorted[1], intersect, image, c);
            }
        }
    }
}

// Main
int main(){

    // A sample of color(s) to play with
    ColorRGB red;
    red.r = 255; red.g = 0; red.b = 0;
      
    ColorRGB blue;
    blue.r = 0; blue.g = 0; blue.b = 255;
    
    // Points for our Line
    Vec2 line[2] = {Vec2(0,0), Vec2(100,100)};

    // Set the fill mode
    glPolygonMode(LINE);

    // Draw a line
     drawLine(line[0],line[1],canvas,red);

    // Data for our triangle
    Vec2 tri[3] = {Vec2(160,60),Vec2(150,10),Vec2(75,190)};
    Vec2 trianglePts[3] = { Vec2(150, 290), Vec2(100, 10), Vec2(200, 190) };
    Vec2 secondTrianglePts[3] = { Vec2(200, 80), Vec2(280, 20), Vec2(170, 60) };
    Vec2 thirdTrianglePts[3] = { Vec2(60, 300), Vec2(40, 10), Vec2(30, 200) };    

    glPolygonMode(FILL);

    triangle(trianglePts[0], trianglePts[1], trianglePts[2], canvas, blue);
    triangle(secondTrianglePts[0], secondTrianglePts[1], secondTrianglePts[2], canvas, blue);
    triangle(thirdTrianglePts[0], thirdTrianglePts[1], thirdTrianglePts[2], canvas, blue);


    // Output the final image
    canvas.outputTGAImage("graphics_lab2.ppm");

    return 0;
}
