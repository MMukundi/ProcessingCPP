#include "Processing.h"
#include "fstream"

GLuint Shader::CompileShader(const char* src, GLenum type){
  GLuint id = glCreateShader(type);

  glShaderSource(id, 1,&src, nullptr);
  glCompileShader(id);
  
  int res;
  glGetShaderiv(id, GL_COMPILE_STATUS, &res);
  
  if(res==GL_FALSE){
    int len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);  
    char* message = (char*)alloca(sizeof(char)*len);
    glGetShaderInfoLog(id, len, &len,message);
    printf("FAILED TO COMPILE\n");
    printf("%s",message);
    return 0;
  }
  
  return id;
}
 
GLuint Shader::CreateShader(const char* vertexShader,const char* fragmentShader)
{
  GLuint prog=glCreateProgram();
  GLuint vs=CompileShader(vertexShader, GL_VERTEX_SHADER);
  GLuint fs=CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
  glAttachShader(prog,vs);
  glAttachShader(prog,fs);
  glLinkProgram(prog);
  glValidateProgram(prog);
  glDeleteShader(vs);
  glDeleteShader(fs);

  return prog;
}
GLuint Shader::ParseShader(const std::string file){
    return CreateShader("VS","FS");
}
