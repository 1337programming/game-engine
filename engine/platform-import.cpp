#ifdef _WIN32
  #include <Gl/glew.h>
#elif __APPLE__

  #include <OpenGL/gl3.h>

#elif __linux__
// linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif