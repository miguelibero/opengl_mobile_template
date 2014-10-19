
#ifndef OpenglGame_ShaderComponent_h
#define OpenglGame_ShaderComponent_h

#include <entityx/entityx.h>
#include <base/Gl.hpp>

struct ShaderComponent : public entityx::Component<ShaderComponent>
{
	std::string vertex;
	std::string fragment;
    GLuint program;
    
    ShaderComponent(const std::string& vertex, const std::string& fragment="", GLuint program=0):
    vertex(vertex), fragment(fragment.empty() ? vertex : fragment), program(program)
    {
    }
};


#endif
