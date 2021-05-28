//#include "stopwatch.h"

//Stopwatch::Stopwatch()
//{
//    void* currentfFont;


//}

//void Stopwatch::drawString(float x, float y, float z, char *string) {
//  glRasterPos3f(x, y, z);

//  for (char* c = string; *c != '\0'; c++) {
//    glutBitmapCharacter(currentFont, *c);  // Updates the position
//  }
//}

//void reshape(int w, int h) {
//  GLfloat aspect;

//  // Save the width and height for text processing
//  width = w;
//  height = h;

//  glViewport(0, 0, (GLsizei) w, (GLsizei) h);

//  glMatrixMode(GL_PROJECTION);

//  glLoadIdentity();

//  if (w <= h) {
//    aspect = (GLfloat) h / (GLfloat) w;
//    glOrtho(-1.5, 1.5, -1.5 * aspect, 1.5 * aspect, -10.0, 10.0);
//  } else {
//    aspect = (GLfloat) w / (GLfloat) h;
//    glOrtho(-1.5 * aspect, 1.5 * aspect, -1.5, 1.5, -10.0, 10.0);
//  }
//}

//void Stopwatch::display() {
//  glClear(GL_COLOR_BUFFER_BIT);
//  glColor3f(0.0, 0.0, 0.0);

//  // Set things up so that we can render text in
//  // window coordinates
//  beginText();

//  // Render the text
//  drawString(0.0, 0.0, "James Madison University");

//  // Set things up for normal rendering
//  endText();

//  // Normal rendering of the scene goes here

//  glFlush();
//}
