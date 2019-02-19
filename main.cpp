#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "CImg.h"

const unsigned char red[] = {255, 0, 0}, green[] = {0, 255, 0}, blue[] = {0, 0, 255};

struct Vertex {
    float x;
    float y;
    float z;
};

struct Face {
    Vertex* v1;
    Vertex* v2;
    Vertex* v3;
};

void getVertex(Vertex* v, std::string s);

void getFace(Face* f, std::string s, std::vector<Vertex*>* vertices);

void loadOBJFile(std::string s, std::vector<Vertex*>* vertices, std::vector<Face*>* faces);

void joinVertices(Vertex* v1, Vertex* v2, cimg_library::CImg<unsigned char> image);

int main() {
    cimg_library::CImg<unsigned char> image(800, 600, 1, 3, 0);
    image.draw_line(-100, -100, 200, 300, red);
    cimg_library::CImgDisplay main_disp(image, "Main");

    std::vector<Vertex*>* vertices;
    std::vector<Face*>* faces;

    loadOBJFile("icoSphere.obj", vertices, faces);

    while(!main_disp.is_closed()) {
        main_disp.wait();
    }

    return 0;
}

void getVertex(Vertex* v, std::string s) {
    std::string::size_type az;
    std::string::size_type bz;

    v->x = std::stof(s, &az);
    v->y = std::stof(s.substr(az), &bz);
    v->z = std::stof(s.substr(bz)); 
}

void getFace(Face* f, std::string s, std::vector<Vertex*>* vertices) {
    std::string::size_type az;

    f->v1 = vertices->at(std::stoi(s)-1);
    s = s.substr(s.find(" ")+1);

    f->v2 = vertices->at(std::stoi(s)-1);
    s = s.substr(s.find(" ")+1);
    
    f->v3 = vertices->at(std::stoi(s)-1);
    s = s.substr(s.find(" ")+1);
}

void loadOBJFile(std::string s, std::vector<Vertex*>* vertices, std::vector<Face*>* faces) {
    std::ifstream infile;
    std::string readLine;
    infile.open(s.c_str());

    while(infile) {
        std::getline(infile, readLine);
        if (readLine.at(0) == 'v' && readLine.at(1) == ' ') {
            Vertex* v = new Vertex;
            getVertex(v, readLine.substr(2));
            vertices->push_back(v);
        }
        else if (readLine.at(0) == 'f' && readLine.at(1) == ' ') {
            Face* f = new Face;
            getFace(f, readLine.substr(2), vertices);
            faces->push_back(f);
        }
    }

}

void joinVertices(Vertex* v1, Vertex* v2, cimg_library::CImg<unsigned char> image) {
    int x0 = (v1->x+1.);
    int y0 = (v1->y+1.);
    int x1 = (v1->x+1.);
    int y1 = (v1->y+1.);
    
    image.draw_line(x0, y0, x1, y1, red);
}