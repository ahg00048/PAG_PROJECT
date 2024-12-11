//
// Created by ahues on 11/12/2024.
//

#ifndef PAG_PROJECT_TEXTURE_H
#define PAG_PROJECT_TEXTURE_H

#include <lodePng.h>

#include <vector>

namespace PAG {
    class Texture {
    private:
        std::vector<unsigned char> _pixels;
        unsigned int _width, _height;
        bool _error = false;
    public:
        Texture() = default;
        Texture(const Texture& orig) = default;
        ~Texture() = default;

        void load(const std::string& path);
        bool success() const;
    };
} // PAG

#endif //PAG_PROJECT_TEXTURE_H
