/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-aboh-daniel-cedrick.kakou
** File description:
** Opener
*/

#ifndef OPENER_HPP_
#define OPENER_HPP_
#include "Arcade.hpp"
#include "Errors.hpp"
#include <dlfcn.h>
#include <functional>
typedef std::shared_ptr<Arcade::IGraphicalModule>(*graphics)();
typedef std::shared_ptr<Arcade::IGameModule>(*games)();
typedef std::shared_ptr<Arcade::Core>(*coreFunc)(const std::string &);

template <typename T>
class Opener {
    public:
        static void * openLib(const std::string &path) {
            void *handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);

            if (handle == nullptr)
                throw Errors::ArcadeError(dlerror(), "Opener::openLib, line 17, Opener.cpp");
            return (handle);
        }
        static T getFunctions(void *handle, const std::string &func) {
            T entry_point = (T)dlsym(handle, func.c_str());

            if (entry_point == nullptr)
                throw Errors::ArcadeError(dlerror(), "Opener::getFunctions, line 21, Opener.hpp");
            return (entry_point);
        }
        static void closeLib(void *handle) {
            dlclose(handle);
        }
    protected:
};

#endif /* !OPENER_HPP_ */
