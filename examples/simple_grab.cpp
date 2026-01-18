#include "wcap.hpp"
#include <iostream>
#include <chrono>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    std::cout << "Initializing Wcap..." << std::endl;
    wcap::ScreenCapture cap;

    std::cout << "Select capture type:\n1. Screen\n2. Window\n3. Any\n> ";
    int choice;
    std::cin >> choice;
    
    wcap::CaptureType type = wcap::CaptureType::Any;
    if (choice == 1) type = wcap::CaptureType::Screen;
    if (choice == 2) type = wcap::CaptureType::Window;

    if (!cap.select_source(type)) {
        std::cerr << "Denied." << std::endl;
        return 1;
    }

    std::cout << "Capturing 100 frames..." << std::endl;

    for (int i = 0; i < 100; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto frame = cap.get_frame();
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double, std::milli> elapsed = end - start;

        if (frame.data.empty()) {
            std::cout << "Stream ended or error." << std::endl;
            break;
        }

        std::cout << "Frame " << i 
                  << ": " << frame.width << "x" << frame.height 
                  << " | Processing Time: " << elapsed.count() << " ms" 
                  << std::endl;

        if (i == 99) {
            std::vector<uint8_t> png_data = frame.data;
            uint8_t* p = png_data.data();
            for (size_t k = 0; k < png_data.size(); k += 3) std::swap(p[k], p[k+2]);
            stbi_write_png("snapshot.png", frame.width, frame.height, 3, p, frame.width * 3);
            std::cout << "Saved snapshot.png" << std::endl;
        }
    }
    cap.stop();
    return 0;
}