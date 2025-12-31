cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

# Use C++ 17 for modern features
set(CMAKE_CXX_STANDARD 17)

# 1. Find the libraries you installed via 'apt'
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# 2. Add your source files
file(GLOB SOURCES "src/*.cpp")

# 3. Create the executable
add_executable(engine ${SOURCES})

# 4. Tell the compiler where to find header files
target_include_directories(engine PRIVATE include)

# 5. Link the libraries to your program
target_link_libraries(engine PRIVATE 
    SDL2::SDL2 
    GLEW::GLEW 
    OpenGL::GL
)