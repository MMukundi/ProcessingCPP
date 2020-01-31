#if !defined(PROCESSING_NAMESPACE_H)

#define PROCESSING_NAMESPACE_H
#include "GLLibs.h"
#include <cmath>
#include <functional>
#define FILL_VALUE __FILL__COLOR__.r, __FILL__COLOR__.g, __FILL__COLOR__.b, (__FILL__VARIABLE__ ? __FILL__COLOR__.a : 0.f)
#define STROKE_VALUE __STROKE__COLOR__.r, __STROKE__COLOR__.g, __STROKE__COLOR__.b, (__STROKE__VARIABLE__ ? __STROKE__COLOR__.a : 0.f)

#define Func std::function<float(float)>
class Event{

};
class MouseEvent: public Event{
    public:
    int button=-1;
    int x;
    int y;
    int dx; 
    int dy;
};
class Shader
{
public:
    static GLuint CompileShader(const char *source, GLenum type);
    static GLuint CreateShader(const char *vertexShader, const char *framentShader);
    static GLuint ParseShader(const std::string shaderPath);
};
enum Shapes
{
    Points = GL_POINTS,
    Lines = GL_LINES,
    LineStrip = GL_LINE_STRIP,
    LineLoop = GL_LINE_LOOP,

    TriangleStrip = GL_TRIANGLE_STRIP,
    TriangleFan = GL_TRIANGLE_FAN,
    QuadStrip = GL_QUAD_STRIP,
    Triangles = GL_TRIANGLES,

    //Affected by fill
    Quad = GL_QUADS,
    Polygon = GL_POLYGON
};
class Color
{
public:
    Color(std::initializer_list<float> c)
    {
        if (c.size() == 1)
        {
            r = *c.begin();
            g = r;
            b = r;
            a = r;
        }
        else if (c.size() == 3)
        {
            auto p = c.begin();
            r = *(p++);
            g = *(p++);
            b = *(p++);
        }
        else
        {
            auto p = c.begin();
            r = *(p++);
            g = *(p++);
            b = *(p++);
            a = *p;
        }
    };
    float r = 255;
    float g = 255;
    float b = 255;
    float a = 255;
};
class Processing
{
public:
    Processing(int w = 100, int h = 100, const char*  t = "Processing") : width(w), height(h),title(t){};
    int width, height;
    double mouseX,mouseY;
    //float horizScale=1, vertScale=1;
    const char* title;
    bool __RUN__ = false;
    GLFWwindow *window = nullptr;
    void size(int w, int h);
    virtual void setup() = 0;
    virtual void draw() = 0;
    virtual void onResize(int w, int h)
    {};
    virtual void onMouseMove(MouseEvent)
    {};
    virtual void mousePressed()
    {};
    virtual void onKeyEvent(int key, int scancode, int action, int mods)
    {};
    void run();

    static inline const Func CosineMap = [](float x) { return (1 - cos(M_PI * x)) / 2; };
    static inline const Func LinearMap = [](float x) { return x; };
    static inline const Func RationalMap = [](float x) { return 4 * x / (3 * x + 1); };

    static float constrain(float value, float min, float max);
    static float constrainMap(float percent, float newLowest, float newHighest, Func mappingFunction = LinearMap);
    static float constrainMap(float value, float lowestValue, float hightestValue, float newLowest, float newHighest, Func mappingFunction = LinearMap);
    static float map(float percent, float newLowest, float newHighest, Func mappingFunction = LinearMap);
    static float map(float value, float lowestValue, float hightestValue, float newLowest, float newHighest, Func mappingFunction = LinearMap);

    void line(float, float, float, float);

    //const auto beginShape = glBegin;
    void beginShape(Shapes);
    static inline const auto endShape = glEnd;
    static inline const auto rotate = glRotatef;

    void strokeWeight(float);

    Color __STROKE__COLOR__ = Color{0, 0, 0,255};
    Color __FILL__COLOR__ = Color{255, 255, 255,255};
    Color __BACKGROUND__COLOR__ = Color{255, 255, 255,255};

    bool __FILL__VARIABLE__ = true;
    bool __STROKE__VARIABLE__ = false;
    float __STROKE__WEIGHT__ = 1;

    float MaxColorValue = 255;

    void vertex(float, float);
    void vertex(float, float, float);

    void background(Color c);
    void background(float);
    void background(float, float, float);
    void background(float r, float g, float b, float a);

    void color(Color c);
    void color(float);
    void color(float, float, float);
    void color(float r, float g, float b, float a);

    void fill(Color);
    void fill(float);
    void fill(float, float, float);
    void noFill();

    void stroke(Color);
    void stroke(float);
    void stroke(float, float, float);
    void noStroke();

    void point(float, float);
    void point(float, float, float);

    void rect(float, float, float, float);

    void circle(float, float, float);

    void text(float, float, const char *, float = 20);
};     // class Processing
#endif // PROCESSING_NAMESPACE_H
