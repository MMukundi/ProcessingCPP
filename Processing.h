#if !defined(PROCESSING_NAMESPACE_H)

#define PROCESSING_NAMESPACE_H
#include "GLLibs.h"
#include <cmath>
#include <functional>
#define FILL_VALUE __FILL__COLOR__.r, __FILL__COLOR__.g, __FILL__COLOR__.b, (__FILL__VARIABLE__ ? __FILL__COLOR__.a : 0.f)
#define STROKE_VALUE __STROKE__COLOR__.r, __STROKE__COLOR__.g, __STROKE__COLOR__.b, (__STROKE__VARIABLE__ ? __STROKE__COLOR__.a : 0.f)

#define Func std::function<float(float)>
class Event
{
};
class MouseEvent : public Event
{
public:
    int button = -1;
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
/** An encapsulation of the functionality of the Processing API
 * Provides graphics capabilities in the C++ language, as well as the structure for event handling
*/
class Processing
{
public:
    /** Creates a window with the specified width and height and with the specified window title*/
    Processing(int w = 100, int h = 100, const char *t = "Processing") : width(w), height(h), title(t){};

    /** The width of the window in screen coordinates*/
    int width;
    /** The height of the window in screen coordinates*/
    int height;

    /** The current x-coordinate of the mouse in screen coordinates*/
    double mouseX;
    /** The current y-coordinate of the mouse in screen coordinates*/
    double mouseY;

    /** The title of the window*/
    const char *title;

    /** The GLFWwindow this instance encapsulates*/
    GLFWwindow *window = nullptr;
    
    //void size(int w, int h);

    /** Called before the main loop of the window */
    virtual void setup() = 0;
    /** Called during the main loop of the window */
    virtual void draw() = 0;

    /** Called every time the window is resized */
    virtual void onResize(int w, int h){};
    /** Called every time the window mouse is moved*/
    virtual void onMouseMove(MouseEvent me){};
    /** Called every time the mouse buttons are pressed*/
    virtual void mousePressed(){};
    /** Called every time a keys is pressed*/
    virtual void onKeyEvent(int key, int scancode, int action, int mods){};

    /** Initializes and runs the window*/
    void run();

    /** Returns a floating point value from 0-1 with a distribution determined by the cosine function*/
    static inline const Func CosineMap = [](float x) { return (1 - cos(M_PI * x)) / 2; };
    /** Returns a floating point value from 0-1 with a distribution determined by the linear function*/
    static inline const Func LinearMap = [](float x) { return x; };
    /** Returns a floating point value from 0-1 with a distribution determined by the rational function*/
    static inline const Func RationalMap = [](float x) { return 4 * x / (3 * x + 1); };

    /** Returns the given value constrained between the supplied minimum and maximum*/
    static float constrain(float value, float min, float max);
    /** Returns the value a given percent (constrained between 0 and 1) between the minimum and maximum*/
    static float constrainMap(float percent, float newLowest, float newHighest, Func mappingFunction = LinearMap);
    /** Constrains the mapping of a value in one range to another according to the provided mapping funtion*/
    static float constrainMap(float value, float lowestValue, float hightestValue, float newLowest, float newHighest, Func mappingFunction = LinearMap);
    /** Returns the value a given percent between the minimum and maximum*/
    static float map(float percent, float newLowest, float newHighest, Func mappingFunction = LinearMap);
    /** Maps a value in one range to another according to the provided mapping funtion*/
    static float map(float value, float lowestValue, float hightestValue, float newLowest, float newHighest, Func mappingFunction = LinearMap);

    /** Creates a line between the specified points*/
    void line(float x1, float y1, float x2, float y2);

    /** Starts the creation of one of the shapes supplied in the Shapes enum*/
    void beginShape(Shapes s);
    /** Ends the creation the current shape*/
    static inline const auto endShape = glEnd;
    /** Rotates the space around the provided vector*/
    static inline const auto rotate = glRotatef;

    /** Determines the width of the lines, outlines, and points drawn*/
    void strokeWeight(float weight);

 
    /** The current run status of the window*/
    bool __RUN__ = false;

    /** The current color of the lines drawn*/
    Color __STROKE__COLOR__ = Color{0, 0, 0, 255};
    /** The current color of the fill inside shapes drawn*/
    Color __FILL__COLOR__ = Color{255, 255, 255, 255};
    /** The current background color of the window*/
    Color __BACKGROUND__COLOR__ = Color{255, 255, 255, 255};

    /** Determines whether or not the shapes drawn are filled in*/
    bool __FILL__VARIABLE__ = true;
    /** Determines whether or not there is a stroke prescent in the shapes*/
    bool __STROKE__VARIABLE__ = false;
    /** Determines the width of the lines drawn*/
    float __STROKE__WEIGHT__ = 1;

    /** Determines the scale of the color values*/
    float MaxColorValue = 255;

    /** Creates a two dimensional vertex in the current shape at the points with the appropriate screen coordinates
    * Must be between with a call to beginShape and endShape*/
    void vertex(float x, float y);

    /** Creates a three dimensional vertex in the current shape at the points with the appropriate screen coordinates
    * Must be between with a call to beginShape and endShape*/
    void vertex(float x, float y, float z);

    /** Sets the background of the window based on the provided Color*/
    void background(Color c);
    /** Sets the background of the window to the grayscale value provided*/
    void background(float grayscale);
    /** Sets the background of the window to the (r,g,b) value provided*/
    void background(float r, float g, float b);
    /** Sets the background of the window to the (r,g,b,a) value provided*/
    void background(float r, float g, float b, float a);

    /** Sets the color of drawn elements to the provided Color*/
    void color(Color c);
    /** Sets the color of drawn elements to the grayscale value provided*/
    void color(float grayscale);
    /** Sets the color of drawn elements to the (r,g,b) value provided*/
    void color(float r, float g, float b);
    /** Sets the color of drawn elements to the (r,g,b,a) value provided*/
    void color(float r, float g, float b, float a);

    /** Sets the color of filled-in shapes to the provided Color*/
    void fill(Color c);
    /** Sets the color of filled-in shapes to the grayscale value provided*/
    void fill(float grayscale);
    /** Sets the color of filled-in shapes to the (r,g,b) value provided*/
    void fill(float r, float g, float b);
    /** Sets the color of filled-in shapes to the (r,g,b,a) value provided*/
    void fill(float r, float g, float b, float a);

    /** Ensures all shapes are not filled in*/
    void noFill();

    /** Sets the color of lines, points, and outlines to the provided Color*/
    void stroke(Color c);
    /** Sets the color of lines, points, and outlines to the grayscale value provided*/
    void stroke(float grayscale);
    /** Sets the color of lines, points, and outlines to the (r,g,b) value provided*/
    void stroke(float r, float g, float b);
    /** Sets the color of lines, points, and outlines to the (r,g,b) value provided*/
    void stroke(float r, float g, float b,float a);
    /** Ensures all lines, points, and outlines are not drawn*/
    void noStroke();

    /** Draws a point in two dimensions*/
    void point(float x, float y);
    /** Draws a point in three dimensions*/
    void point(float x, float y, float z);

    /** Draws a rectangle between with a top left corner at (x,y) with the specified width and height*/
    void rect(float x, float y, float w, float h);
    /** Draws a circle centered at (x,y) with the specified radius*/
    void circle(float x, float y, float r);

    /** Draws the provided string with (x,y) at the bottom left corner
     * [ONLY NUMERICAL STRINGS ARE CURRENTLY SUPPORTED]
    */
    void text(float x, float y, const char *string, float size = 20);
};     // class Processing
#endif // PROCESSING_NAMESPACE_H
