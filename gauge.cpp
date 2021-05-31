#include "gauge.h"

Gauge::Gauge() {
    rate = 1.0;
}

// Affichage de la jauge
void Gauge::display() {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(2.0 * (1.0 - rate), 2.0 * rate, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-4.0 + 8.0 * (1 - rate), 6.0, 10);
    glVertex3f(-4.0 + 8.0 * (1 - rate), 5.0, 10);
    glVertex3f(4.0, 5.0, 10);
    glVertex3f(4.0, 6.0, 10);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Gauge::decrease() {
    rate -= 0.002;
    if (rate < 0)
        rate = 0.0;
}

void Gauge::addFuel() {
    rate += 0.3;
    if (rate > 1.0) {
        rate = 1.0;
    }
}



