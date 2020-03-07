class PPM {
public: 

    //3 char per pixel (R, G, B)
    PPM(unsigned int width, unsigned int height) {
        pixelData = new unsigned char[width * height * 3];
    }

    ~PPM() {
        delete[] pixelData;
    }

private:    
    unsigned char* pixelData;

};


int main() {

    PPM myPPM(64, 128);

    return 0;
}