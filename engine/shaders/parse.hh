#include <sstream>

namespace Engine
{
    namespace Shaders
    {
        struct ProgramSource
        {
            std::string VertexSource;
            std::string FragmentSource;
        };

        ProgramSource Parse(std::istream& path);
    }
}
