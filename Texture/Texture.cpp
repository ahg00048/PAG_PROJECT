//
// Created by ahues on 11/12/2024.
//

#include "Texture.h"

#include <stdexcept>
#include <glad/glad.h>

namespace PAG {
    void Texture::load(const std::string& path) {
        _error = lodepng::decode (_pixels, _width, _height, path);

        if(_error) {
            std::string mensaje = path + " no se pudo cargar";
            throw std::runtime_error(mensaje);
        }
        // La textura se carga del revés, así que vamos a darle la vuelta
        unsigned char *imgPtr = &_pixels[0];
        int colorNComponents = 4;
        int widthIncrease = _width * colorNComponents; // Ancho en bytes
        unsigned char* top = nullptr;
        unsigned char* bot = nullptr;
        unsigned char* temp = nullptr;

        for(int i = 0; i < _height / 2; i++) {
            top = imgPtr + i * widthIncrease;
            bot = imgPtr + (_height - i - 1) * widthIncrease;

            for(int j = 0; j < widthIncrease; j++) {
                memcpy(temp, top, sizeof(unsigned char));
                memcpy(top, bot, sizeof(unsigned char));
                memcpy(bot, temp, sizeof(unsigned char));
                ++top;
                ++bot;
            }
        }

        // Finalmente, pasamos la textura a OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels.data());
    }

    bool Texture::success() const {
        return !_error;
    }
} // PAG