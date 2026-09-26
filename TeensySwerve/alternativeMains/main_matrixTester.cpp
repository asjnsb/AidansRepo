#include <Arduino.h>
#include <my_cpp_functions/myLEDMatrix.h>


void drawTriangles();
void drawPixelChase();

int i = 0;
int pass = 0;
int x = 0;
int y = 0;
float change = 1.0/8.0;
float drivePower[] = {0.0,0.0};
float weaponPower[] = {0.5,0.5};
bool increasing = true;
uint16_t color[] = {
    matrix.Color(0, 255, 0),
    matrix.Color(255, 0, 0), 
    matrix.Color(255, 255, 0)
};

void setup(){
    matrixInit(1);
    
    blinkLED(3, 150, "white");
}

void loop(){
    matrixUpdate(matrix.Color(255,0,255), drivePower, weaponPower);

    if (increasing){
        drivePower[0]  += change;
        drivePower[1]  += change;
        weaponPower[0] += change/2;
        weaponPower[1] += change/2;
    } else {
        drivePower[0]  -= change;
        drivePower[1]  -= change;
        weaponPower[0] -= change/2;
        weaponPower[1] -= change/2;
    }

    if (drivePower[0] > 1.0) increasing = false;
    if (drivePower[0] < -1.0) increasing = true;
    
    delay(100);
}


//======================functions=====================================

void drawTriangles(){
    switch (pass++)
    {
    case 0:
        //top triangle
        matrix.drawFastHLine(1, 0, 6, color[i]);
        matrix.drawFastHLine(2, 1, 4, color[i]);
        matrix.drawFastHLine(3, 2, 2, color[i]);
        matrix.drawFastHLine(4, 3, 1, color[i]);
        break;
    case 1:
        //right triangle
        matrix.drawFastVLine(7, 1, 6, color[i]);
        matrix.drawFastVLine(6, 2, 4, color[i]);
        matrix.drawFastVLine(5, 3, 2, color[i]);
        matrix.drawFastVLine(4, 4, 1, color[i]);
        break;
    case 2:
        //bottom triangle
        matrix.drawFastHLine(1, 7, 6, color[i]);
        matrix.drawFastHLine(2, 6, 4, color[i]);
        matrix.drawFastHLine(3, 5, 2, color[i]);
        matrix.drawFastHLine(3, 4, 1, color[i]);
        break;
    case 3:
        //left triangle
        matrix.drawFastVLine(0, 1, 6, color[i]);
        matrix.drawFastVLine(1, 2, 4, color[i]);
        matrix.drawFastVLine(2, 3, 2, color[i]);
        matrix.drawFastVLine(3, 3, 1, color[i]);
        pass = 0;
        break;

    default:
        pass = 0;
        break;
    }

    if (++i > 1) i=0;
}

void drawPixelChase() {
    
    matrix.clear(); // needed to show the thing you're actually doing rather than just streaks
    
    matrix.drawPixel(x, y, matrix.Color(255, 255, 255));

    if (++x >= matrix.width()) {
        y++;
        x = 0;
    }
    if (y >= matrix.height()) y = 0;

    delay(250);
}