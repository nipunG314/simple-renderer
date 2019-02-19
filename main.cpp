#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "CImg.h"
#include "Eigen/Dense"

#define Vector3 Eigen::Vector3f

const unsigned char red[] = {255, 0, 0}, green[] = {0, 255, 0}, blue[] = {0, 0, 255};

typedef Vector3 Vertex;

struct Face {
    Vertex v1;
    Vertex v2;
    Vertex v3;
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

struct Camera {
    Vector3* position;
    Vector3* view_dir;
    float inclination;
};

const Vertex& getVertex(std::string s);

const Face& getFace(std::string s, std::vector<Vertex>* vertices);

const Mesh& loadOBJFile(std::string s);

int main() {
    cimg_library::CImg<unsigned char> image(800, 600, 1, 3, 0);
    cimg_library::CImgDisplay main_disp(image, "Main");

    const Mesh& mesh = loadOBJFile("icoSphere.obj");

    while(!main_disp.is_closed()) {
        main_disp.wait();
    }

    return 0;
}

const Vertex& getVertex(std::string s) {
    std::string::size_type az;
    std::string::size_type bz;

    float x, y, z;

    x = std::stof(s, &az);
    y = std::stof(s.substr(az), &bz);
    z = std::stof(s.substr(bz));

    const Vertex& v = Vector3::Constant(x, y, z);
    return v; 
}

const Face& getFace(std::string s, std::vector<Vertex>* vertices) {
    std::string::size_type az;

    Vertex v1, v2, v3;

    v1 = vertices->at(std::stoi(s)-1);
    s = s.substr(s.find(" ")+1);

    v2 = vertices->at(std::stoi(s)-1);
    s = s.substr(s.find(" ")+1);
    
    v3 = vertices->at(std::stoi(s)-1);
    s = s.substr(s.find(" ")+1);

    const Face& f = { v1, v2, v3 };
    return f;
}

const Mesh& loadOBJFile(std::string s) {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    std::ifstream infile;
    std::string readLine;
    infile.open(s.c_str());

    while(infile) {
        std::getline(infile, readLine);
        if (readLine.at(0) == 'v' && readLine.at(1) == ' ') {
            const Vertex& v = getVertex(readLine.substr(2));
            vertices.push_back(v);
        }
        else if (readLine.at(0) == 'f' && readLine.at(1) == ' ') {
            const Face& f = getFace(readLine.substr(2), &vertices);
            faces.push_back(f);
        }
    }

    const Mesh& = { vertices, faces };

}