CONFIG(debug,debug|release) {
  DEFINES += "__DEBUG=true" "__LOG=true"
}
#DEFINES += "__DLOG=true"

#__DEBUG will make asserts on all risky operations, and will output a detailed error message if it fails
#__LOG will output all VBE_LOG(..). This is general (important) info such as resource loading, etc
#__DLOG will output all VBE_DLOG(..). This is detailed log info, use it for debugging.
# Disable all three for faster internets

TEMPLATE = app
CONFIG -= qt
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
INCLUDEPATH += $$PWD/
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
    $$PWD/main.cpp \
    $$PWD/Game.cpp \
	$$PWD/tools.cpp \
    $$PWD/graphics/Texture.cpp \
    $$PWD/graphics/TextureManager.cpp \
    $$PWD/graphics/Shader.cpp \
	$$PWD/graphics/ShaderProgram.cpp \
	$$PWD/audio/AudioManager.cpp \
    $$PWD/input/InputManager.cpp \
    $$PWD/SceneMain/SceneMain.cpp \
	$$PWD/GameObject.cpp \
	$$PWD/SceneMain/TexturedObject.cpp \
	$$PWD/graphics/Mesh.cpp \
	$$PWD/graphics/Vertex.cpp \
	$$PWD/graphics/Model.cpp \
	$$PWD/graphics/Uniform.cpp \
	$$PWD/graphics/ShaderBinding.cpp \
	$$PWD/SceneMain/RegularPolygonObject.cpp \
	$$PWD/graphics/MeshManager.cpp \
	$$PWD/graphics/ShaderManager.cpp \
    SceneMain/PerspectiveCamera.cpp

HEADERS += \
    $$PWD/Game.hpp \
    $$PWD/tools.hpp \
    $$PWD/graphics/Texture.hpp \
	$$PWD/graphics/TextureManager.hpp \
    $$PWD/graphics/Shader.hpp \
    $$PWD/graphics/ShaderProgram.hpp \
	$$PWD/audio/AudioManager.hpp \
    $$PWD/input/InputManager.hpp \
    $$PWD/SceneMain/SceneMain.hpp \
	$$PWD/GameObject.hpp \
	$$PWD/glm/*.hpp \
	$$PWD/SceneMain/TexturedObject.hpp \
	$$PWD/graphics/Mesh.hpp \
	$$PWD/graphics/Vertex.hpp \
	$$PWD/graphics/Model.hpp \
	$$PWD/graphics/Uniform.hpp \
	$$PWD/graphics/ShaderBinding.hpp \
	$$PWD/SceneMain/RegularPolygonObject.hpp \
	$$PWD/graphics/MeshManager.hpp \
	$$PWD/graphics/ShaderManager.hpp \
    SceneMain/PerspectiveCamera.hpp

OTHER_FILES += \
	$$PWD/data/shaders/sample.vert \
	$$PWD/data/shaders/sample.frag \
	$$PWD/data/shaders/sample2.vert \
	$$PWD/data/shaders/sample2.frag
