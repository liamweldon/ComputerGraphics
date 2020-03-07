#include <iostream>
#include <fstream>
#include <string> 

#include "PPM.h"

// Constructor loads a filename with the .ppm extension
// TODO: could be safer
PPM::PPM(std::string fileName){
    std::ifstream inFile;
    
    inFile.open(fileName);
    if (inFile.is_open()) {
        std::string line;
        // line 1, P3
        getline(inFile, line);
        
        // line 2, comment
        getline(inFile, line);

        // line 3, w x h
        getline(inFile, line);
        int i = 0;
        while (i < line.length()) {
            if (line.at(i) == ' ') {
                std::string wString = line.substr(0, i);
                std::string hString = line.substr(i + 1, line.length());
                m_width = std::stoi(wString);
                m_height = std::stoi(hString);
                break;
            }
            i++;
        }
        m_PixelData = new unsigned char[m_width * m_height * 3];

        // line 4, 255
        getline(inFile, line);

        // this will break horribly if line 3 lies about widht and height 
        int y = 0;
        int x = 0;
        i = 0;
        unsigned char R;
        unsigned char G;
        unsigned char B;
        while (getline(inFile, line)) {
            if ((i % 3) == 0) {
                R = std::stoi(line);
                i++;
            }
            else if ((i % 3) == 1) {
                G = std::stoi(line);
                i++;
            }
            else if ((i % 3) == 2) {
                B = std::stoi(line);
                i++;
                setPixel(x, y, R, G, B);
                R = -1;
                G = -1;
                B = -1;
                x++;
            }
            if (i % (m_width * 3) == 0) {
                y++;
                x = 0;
            }
        }
    }

    inFile.close();

}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
    delete[] m_PixelData;
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){
    std::ofstream outFile;
    outFile.open(outputFileName);
    if (outFile.is_open()) {
        outFile << "P3" << std::endl;
        outFile << "# Where have all the good men gone, and where are all the gods?" << std::endl;
        outFile << std::to_string(m_width) << " " << std::to_string(m_height) << std::endl;
        outFile << std::to_string(255) << std::endl;
        int i = 0;
        while (i < (3 * m_height * m_width)) {
            outFile << std::to_string(m_PixelData[i]) << std::endl;
            i++;
        }
    }
    outFile.close();

}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken(){
    int i = 0;

    while (i < (3 * m_height * m_width)) {
        int rgbVal = m_PixelData[i];
        if (rgbVal >= 50) {
            rgbVal -= 50;
        }
        else {
            rgbVal = 0;
        }
        m_PixelData[i] = rgbVal;
        i++;
    }
}

// Sets a pixel to a specific R,G,B value 
// TODO: could be safer (check x & y)
void PPM::setPixel(int x, int y, int R, int G, int B){
    // std::cout << "x: " << std::to_string(x) << " y: " << std::to_string(y) << " R: " << std::to_string(R) << " G: " << std::to_string(G) << " B: " << std::to_string(B) << std::endl;
    // 1 row = 3 * m_width, so, (x, y) should = m_PixelData[3((m_width * y) + x)]
    if ((R >= 0) && (G >= 0) && (B >= 0)) {
        int r_loc = 3 * ((m_width * y) + x);
        int g_loc = r_loc + 1;
        int b_loc = g_loc + 1;
        m_PixelData[r_loc] = (unsigned char) R;
        m_PixelData[g_loc] = (unsigned char) G;
        m_PixelData[b_loc] = (unsigned char) B;
    }
    else {
        std::cerr << "invalid RGB values for pixel at (" + std::to_string(x) + "," + std::to_string(y) + ")";
    }

}
