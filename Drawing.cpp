#include "Processing.h"

void Processing::vertex(float x, float y)
{
    color(STROKE_VALUE);
    glVertex2f(x, y);
}
void Processing::vertex(float x, float y, float z)
{
    color(STROKE_VALUE);
    glVertex3f(x, y, z);
}
void Processing::line(float x1, float y1, float x2, float y2)
{
    color(STROKE_VALUE);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}
void Processing::rect(float x, float y, float w, float h)
{
    glColor4f(FILL_VALUE);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x, y+h);
    glVertex2f(x+w, y+h);
    glVertex2f(x+w, y);
    glEnd();
}
void Processing::color(float r, float g, float b)
{
    r /= MaxColorValue;
    g /= MaxColorValue;
    b /= MaxColorValue;
    glColor3f(r, g, b);
}
void Processing::color(float r, float g, float b, float a)
{
    r /= MaxColorValue;
    g /= MaxColorValue;
    b /= MaxColorValue;
    a /= MaxColorValue;
    glColor4f(r, g, b, a);
}
void Processing::color(float grayscale)
{
    grayscale /= MaxColorValue;
    glColor3f(grayscale, grayscale, grayscale);
}
void Processing::color(Color c)
{
    color(c.r, c.g, c.b,c.a);
}

void Processing::point(float x, float y)
{
    color(STROKE_VALUE);
    Color t = __FILL__COLOR__;
    circle(x, y, __STROKE__WEIGHT__ / 2);
    __FILL__COLOR__ = t;
}

void Processing::point(float x, float y, float z)
{
    color(__STROKE__COLOR__);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
}

void Processing::circle(float x, float y, float r)
{
    color(__FILL__VARIABLE__ ? __FILL__COLOR__ : __STROKE__COLOR__);
    glBegin(__FILL__VARIABLE__ ? GL_POLYGON : GL_LINE_LOOP);
    for (float theta = 0, tp = 2 * M_PI; theta <= tp; theta += .01)
        glVertex2f(x + r * cos(theta), y + r * sin(theta));
    glEnd();
}

void Processing::beginShape(Shapes s)
{
    // printf("CCC(%f,%f,%f)\n",__FILL__COLOR__.r,__FILL__COLOR__.g,__FILL__COLOR__.b);
    // printf(__FILL__VARIABLE__ ? "true" : "false");
    color(__FILL__VARIABLE__ ? __FILL__COLOR__ : (s == Polygon || s == Quad ? __STROKE__COLOR__ : __FILL__COLOR__));
    glBegin(__FILL__VARIABLE__ ? s : (s == Polygon || s == Quad ? GL_LINE_LOOP : s));
}
void Processing::fill(Color c)
{
    __FILL__COLOR__ = c;
    __FILL__VARIABLE__ = true;
};
void Processing::fill(float g)
{
    __FILL__COLOR__ = Color{g, g, g};
};
void Processing::fill(float r, float g, float b)
{
    __FILL__COLOR__ = Color{r, g, b};
    __FILL__VARIABLE__ = true;
};
//void fill() { __FILL__VARIABLE__ = true; };
void Processing::noFill() { __FILL__VARIABLE__ = false; };

void Processing::stroke(Color c)
{
    __STROKE__COLOR__ = c;
    __STROKE__VARIABLE__ = true;
};
void Processing::stroke(float g)
{
   __STROKE__COLOR__ = Color{g, g, g};
    __STROKE__VARIABLE__ = true;
};
void Processing::stroke(float r, float g, float b)
{
   __STROKE__COLOR__ = Color{r, g, b};
    __STROKE__VARIABLE__ = true;
};
void Processing::noStroke()
{
    __STROKE__VARIABLE__ = false;
}
//void stroke() { _FILL_VARIABLE_ = true; };

void Processing::strokeWeight(float w)
{
    glLineWidth(w);
    __STROKE__WEIGHT__ = (w);
}
void Processing::background(Color c)
{
    __BACKGROUND__COLOR__ = c;
}
void Processing::background(float g)
{
    __BACKGROUND__COLOR__ = {g, g, g};
}
void Processing::background(float r, float g, float b)
{
    __BACKGROUND__COLOR__ = {r, g, b};
}
void Processing::background(float r, float g, float b, float a)
{
    __BACKGROUND__COLOR__ = {r, g, b, a};
}
void Processing::text(float x, float y, const char *c, float size)
{
    float xsize = (float)size * .8;
    for (int i = 0; c[i] != '\0'; i++, x += size)
        switch (c[i])
        {
        case '-':
        {
            line(x + xsize / 4, y - size / 2, x + xsize * .75, y - size / 2);
        }
        break;
        case ':':
        {
            point(x + xsize / 4, y - 3 * size / 4);
        }
        case '.':
        {
            point(x + xsize / 4, y - size / 4);
            x -= xsize / 2;
        }
        break;
        case '0':
        {
            beginShape(LineLoop);
            vertex(x + xsize, y);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            vertex(x, y);
            endShape();
        }
        break;
        case '1':
        {
            line(x + xsize / 2, y, x + xsize / 2, y - size);
        }
        break;
        case '2':
        {
            beginShape(LineStrip);
            vertex(x + xsize, y);
            vertex(x, y);
            vertex(x, y - size / 2);
            vertex(x + xsize, y - size / 2);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            endShape();
        }
        break;
        case '3':
        {
            beginShape(LineStrip);
            vertex(x, y);
            vertex(x + xsize, y);
            vertex(x + xsize, y - size / 2);
            vertex(x, y - size / 2);
            vertex(x + xsize, y - size / 2);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            endShape();
        }
        break;
        case '4':
        {
            beginShape(LineStrip);
            vertex(x, y - size);
            vertex(x, y - size / 2);
            vertex(x + xsize, y - size / 2);
            vertex(x + xsize, y - size);
            vertex(x + xsize, y);
            endShape();
        }
        break;
        case '5':
        {
            beginShape(LineStrip);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            vertex(x, y - size / 2);
            vertex(x + xsize, y - size / 2);
            vertex(x + xsize, y);
            vertex(x, y);
            endShape();
        }
        break;
        case '6':
        {
            beginShape(LineStrip);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            vertex(x, y - size / 2);
            vertex(x + xsize, y - size / 2);
            vertex(x + xsize, y);
            vertex(x, y);
            vertex(x, y - size / 2);
            endShape();
        }
        break;
        case '7':
        {
            beginShape(LineStrip);
            vertex(x + xsize, y);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            endShape();
        }
        break;
        case '8':
        {
            beginShape(LineLoop);
            vertex(x + xsize, y);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            vertex(x, y);
            endShape();
            line(x, y - size / 2, x + xsize, y - size / 2);
        }
        break;
        case '9':
        {
            beginShape(LineStrip);
            vertex(x, y);
            vertex(x + xsize, y);
            vertex(x + xsize, y - size / 2);
            vertex(x, y - size / 2);
            vertex(x, y - size);
            vertex(x + xsize, y - size);
            vertex(x + xsize, y - size / 2);
            endShape();
        }
        break;
        case 'a':
        case 'A':
        {
            beginShape(LineStrip);
            vertex(x, y);
            vertex(x + xsize / 2, y - size);
            vertex(x + xsize, y);
            endShape();
            line(x + xsize / 4, y - size / 2, x + xsize * .75, y - size / 2);
        }
        break;
        case 'b':
        case 'B':
        {
            beginShape(LineStrip);
            vertex(x, y);
            vertex(x, y - size);
            vertex(x + 2 * size / 3, y - size * .75);
            vertex(x, y - size / 2);
            vertex(x + 2 * size / 3, y - size / 4);
            vertex(x, y);
            endShape();
        }
        break;
        case 'x':
        case 'X':
        {
            beginShape(Lines);
            vertex(x, y);
            vertex(x + xsize, y - size);
            vertex(x, y - size);
            vertex(x + xsize, y);
            endShape();
        }
        break;

        case 'y':
        case 'Y':
        {
            beginShape(LineStrip);
            vertex(x + xsize / 2, y);
            vertex(x + xsize / 2, y - size / 2);
            vertex(x, y - size);
            vertex(x + xsize / 2, y - size / 2);
            vertex(x + xsize, y - size);
            endShape();
        }
        break;

        default:
        {
            beginShape(LineStrip);
            vertex(x, y - 2 * size / 3);
            vertex(x + xsize / 2, y - size);
            vertex(x + xsize, y - 2 * size / 3);
            vertex(x + xsize / 2, y - size / 3);
            vertex(x + xsize / 2, y);
            endShape();
        }
        break;
        }
}