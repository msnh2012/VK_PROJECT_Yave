/*******************************
Copyright (c) 2016-2022 Grégoire Angerand

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**********************************/
#ifndef YAVE_COMPONENTS_SCRIPTWORLDCOMPONENT_H
#define YAVE_COMPONENTS_SCRIPTWORLDCOMPONENT_H

#include <yave/yave.h>

#include <y/core/Vector.h>
#include <y/core/String.h>

#include <y/reflect/reflect.h>

namespace yave {

class ScriptWorldComponent final {
    public:
        struct CompiledScript {
            virtual ~CompiledScript() {
            }

            virtual void run() = 0;
        };

        struct Script {
            core::String name;
            core::String code;

            std::weak_ptr<CompiledScript> compiled;

            y_reflect(Script, name, code);
        };

        const auto& scripts() const {
            return _scripts;
        }

        auto& scripts() {
            return _scripts;
        }

        y_reflect(ScriptWorldComponent, _scripts)

    private:
        core::Vector<Script> _scripts;
};

}

#endif // YAVE_COMPONENTS_SCRIPTWORLDCOMPONENT_H

