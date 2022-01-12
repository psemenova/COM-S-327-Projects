#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "GraphicsClient.h"
using namespace std;


/**
 * @brief Construct a new Graphics Client:: Graphics Client object
 * Constructor
 * 
 * Creates a connection to the server 
 * 
 * @param url the url for the server
 * @param portNumber the port number for the server connection
 */
GraphicsClient::GraphicsClient(std::string inUrl, int portNumber) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf( stderr, "Error creating socket\n");
        exit(-1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portNumber);

    if(inet_pton(AF_INET, inUrl.c_str(), &serv_addr.sin_addr)<=0)
    {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        exit (-1);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        fprintf(stderr, "Connection Failed \n");
        exit (-1);
    }

    url = inUrl;
    portNum = portNumber;   
}

/**
 * @brief Construct a new Graphics Client:: Graphics Client object
 * Copy Constuctor
 * 
 * creates a new connection from an existing object
 * 
 * @param rhs the object to copy the connection from
 */
GraphicsClient::GraphicsClient(const GraphicsClient &rhs){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf( stderr, "Error creating socket\n");
        exit(-1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(rhs.portNum);

    if(inet_pton(AF_INET, rhs.url.c_str(), &serv_addr.sin_addr)<=0)
    {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        exit (-1);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        fprintf(stderr, "Connection Failed \n");
        exit (-1);
    }

    url = rhs.url;
    portNum = rhs.portNum;
}

/**
 * @brief Destroy the Graphics Client:: Graphics Client object
 * Destructor
 * 
 * closes the connection to the server
 * 
 */
GraphicsClient::~GraphicsClient() {
    close(sockfd);
}

/**
 * @brief 
 * operator =
 * 
 * closes the current connection
 * opens a new one from the passed in object
 * 
 * @param rhs the object to copy the connection from
 * @return const GraphicsClient& 
 */
const GraphicsClient &GraphicsClient::operator=(const GraphicsClient &rhs){
    close(sockfd);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf( stderr, "Error creating socket\n");
        exit(-1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(rhs.portNum);

    if(inet_pton(AF_INET, rhs.url.c_str(), &serv_addr.sin_addr)<=0)
    {
        fprintf(stderr, "Invalid address/ Address not supported \n");
        exit (-1);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        fprintf(stderr, "Connection Failed \n");
        exit (-1);
    }

    url = rhs.url;
    portNum = rhs.portNum;

    return *this;
}

/**
 * @brief 
 * takes in the RGB values and sets the background to 
 * the that color
 * 
 * @param R the red color intger
 * @param G the green color intger 
 * @param B the blue color integer
 */
void GraphicsClient::setBackgroundColor(int R, int G, int B) {
    char message[100];

    //SYNC
    message[0] = 0xFF; 

    // size -> 0007 = 7
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x07; 

    //Background Code
    message[5] = 0x02;

    //Background Info
    message[6] = (R >> 4) & 0x0F; // Red
    message[7] = R & 0x0F; // Red
    message[8] = (G >> 4) & 0x0F; // Green
    message[9] = G & 0x0F; // Green
    message[10] = (B >> 4) & 0x0F; // Blue
    message[11] = B & 0x0F; // Blue

    send(sockfd, message, 12, 0);
}

/**
 * @brief 
 * 
 * takes in a color and sets the drawing color
 * 
 * @param R the red color intger
 * @param G the green color intger 
 * @param B the blue color integer
 */
void GraphicsClient::setDrawingColor(int R, int G, int B) {
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size -> 0007 = 7
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x07; 

    // Set Drawing Color Code
    message[5] = 0x06; 

    // Set Drawing Color Info
    message[6] = (R >> 4) & 0x0F; // Red
    message[7] = R & 0x0F; // Red
    message[8] = (G >> 4) & 0x0F; // Green
    message[9] = G & 0x0F; // Green
    message[10] = (B >> 4) & 0x0F; // Blue
    message[11] = B & 0x0F; // Blue

    //send message of length 6
    send(sockfd, message, 12, 0);
}

/**
 * @brief 
 * clears the display to the background color. 
 */
void GraphicsClient::clear(){
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size -> 0001 = 1
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01; 

    //Clear
    message[5] = 0x01; 

    //send message of length 6
    send(sockfd, message, 6, 0);
}

/**
 * @brief 
 * sets the pixel at the location given by the first two 
 * parameters to the color given by the last three parameters.  The first two 
 * parameter are the location given by the x and then y coordinate.  The last three 
 * parameters are the color given by red, green, and blue in that order. 
 * 
 * @param x coordinate
 * @param y coordinate
 * @param R red color int
 * @param G green color int
 * @param B blue color int
 */
void GraphicsClient::setPixel(int x, int y, int R, int G, int B) {
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size ->  15
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x0F;  // TODO - set size

    // Set Pixel Code
    message[5] = 0x02;

    // Set Pixel Info
    // x
    message[6] = (x >> 12) & 0x0F; 
    message[7] = (x >> 8) & 0x0F;
    message[8] = (x >> 4) & 0x0F;
    message[9] = x & 0x0F;
    // y
    message[10] = (y >> 12) & 0x0F; 
    message[11] = (y >> 8) & 0x0F;
    message[12] = (y >> 4) & 0x0F;
    message[13] = y & 0x0F;
    // Red
    message[14] = (R >> 4) & 0x0F;;
    message[15] = R & 0x0F;
    // Green
    message[16] = (G >> 4) & 0x0F;;
    message[17] = G & 0x0F;
    // Blue
    message[18] = (B >> 4) & 0x0F;;
    message[19] = B & 0x0F;


    //send message of length 20
    send(sockfd, message, 20, 0);
}

/**
 * @brief 
 * draws a rectangle at the specified coordinates 
 * given by the first two parameters of the specified size given by the last two 
 * parameters.  The first two parameters are again the x and y coordinate in that 
 * order, and the last two parameters are the width and height, also given in that 
 * order. 
 * @param x coordinate
 * @param y coodinate
 * @param width of the rectangle
 * @param height of the rectangle
 */
void GraphicsClient::drawRectangle(int x, int y, int width, int height) {
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size 
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01;
    message[4] = 0x01; 

    //Draw Rectangle Code
    message[5] = 0x07; 

    // x
    message[6] = (x >> 12) & 0x0F; 
    message[7] = (x >> 8) & 0x0F;
    message[8] = (x >> 4) & 0x0F;
    message[9] = x & 0x0F;

    // y
    message[10] = (y >> 12) & 0x0F; 
    message[11] = (y >> 8) & 0x0F;
    message[12] = (y >> 4) & 0x0F;
    message[13] = y & 0x0F;

    // width
    message[14] = (width >> 12) & 0x0F; 
    message[15] = (width >> 8) & 0x0F;
    message[16] = (width >> 4) & 0x0F;
    message[17] = width & 0x0F;

    // height
    message[18] = (height >> 12) & 0x0F; 
    message[19] = (height >> 8) & 0x0F;
    message[20] = (height >> 4) & 0x0F;
    message[21] = height & 0x0F;

    send(sockfd, message, 22, 0);

}

/**
 * @brief 
 * raws a filled rectangle at the position and size 
 * given by the parameters.  The parameters are the same as the drawRectangle 
 * parameters. 
 * @param x coordinate
 * @param y coordinate
 * @param width of the rectangle
 * @param height of the rectangle
 */
void GraphicsClient::fillRectangle(int x, int y, int width, int height) {
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size -> 
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01;
    message[4] = 0x01; 

    //Fill Rectangle Code
    message[5] = 0x08; 

    // x
    message[6] = (x >> 12) & 0x0F; 
    message[7] = (x >> 8) & 0x0F;
    message[8] = (x >> 4) & 0x0F;
    message[9] = x & 0x0F;

    // y
    message[10] = (y >> 12) & 0x0F; 
    message[11] = (y >> 8) & 0x0F;
    message[12] = (y >> 4) & 0x0F;
    message[13] = y & 0x0F;

    // width
    message[14] = (width >> 12) & 0x0F; 
    message[15] = (width >> 8) & 0x0F;
    message[16] = (width >> 4) & 0x0F;
    message[17] = width & 0x0F;

    // height
    message[18] = (height >> 12) & 0x0F; 
    message[19] = (height >> 8) & 0x0F;
    message[20] = (height >> 4) & 0x0F;
    message[21] = height & 0x0F;

    send(sockfd, message, 22, 0);
}


/**
 * @brief 
 * clears (sets the pixels to the background color) at 
 * the location and size specified by the parameters.  These parameters are the same 
 * as the drawRectangle parameters. 
 * @param x coordinate
 * @param y coordinate
 * @param width of the rectangle
 * @param height of the rectangle
 */
void GraphicsClient::clearRectangle(int x, int y, int width, int height) {
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size -> 
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01;
    message[4] = 0x01; 

    //Clear Rectangle Code
    message[5] = 0x09; 

    // x
    message[6] = (x >> 12) & 0x0F; 
    message[7] = (x >> 8) & 0x0F;
    message[8] = (x >> 4) & 0x0F;
    message[9] = x & 0x0F;

    // y
    message[10] = (y >> 12) & 0x0F; 
    message[11] = (y >> 8) & 0x0F;
    message[12] = (y >> 4) & 0x0F;
    message[13] = y & 0x0F;

    // width
    message[14] = (width >> 12) & 0x0F; 
    message[15] = (width >> 8) & 0x0F;
    message[16] = (width >> 4) & 0x0F;
    message[17] = width & 0x0F;

    // height
    message[18] = (height >> 12) & 0x0F; 
    message[19] = (height >> 8) & 0x0F;
    message[20] = (height >> 4) & 0x0F;
    message[21] = height & 0x0F;

    send(sockfd, message, 22, 0);
}

/**
 * @brief 
 * raws an oval at the specified location inscribed in a 
 * rectangle of the specified size.  The parameters are the same as given in 
 * drawRectangle. 
 * @param x coordinate
 * @param y coordinate
 * @param width of the oval
 * @param height of the oval
 */
void GraphicsClient::drawOval(int x, int y, int width, int height) {
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size -> 
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01;
    message[4] = 0x01; 

    //Draw Oval Code
    message[5] = 0x0A; 

    // x
    message[6] = (x >> 12) & 0x0F; 
    message[7] = (x >> 8) & 0x0F;
    message[8] = (x >> 4) & 0x0F;
    message[9] = x & 0x0F;

    // y
    message[10] = (y >> 12) & 0x0F; 
    message[11] = (y >> 8) & 0x0F;
    message[12] = (y >> 4) & 0x0F;
    message[13] = y & 0x0F;

    // width
    message[14] = (width >> 12) & 0x0F; 
    message[15] = (width >> 8) & 0x0F;
    message[16] = (width >> 4) & 0x0F;
    message[17] = width & 0x0F;

    // height
    message[18] = (height >> 12) & 0x0F; 
    message[19] = (height >> 8) & 0x0F;
    message[20] = (height >> 4) & 0x0F;
    message[21] = height & 0x0F;

    send(sockfd, message, 22, 0);
}

/**
 * @brief 
 * it is the same as the drawOval method except the oval is filled. 
 * @param x coordinate
 * @param y coordinate
 * @param width of the oval
 * @param height of the oval
 */
void GraphicsClient::fillOval(int x, int y, int width, int height) {
    char message[100];
    //SYNC
    message[0] = 0xFF; 

    // size -> 
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01;
    message[4] = 0x01; 

    //Fill Oval Code
    message[5] = 0x0B; 

    // x
    message[6] = (x >> 12) & 0x0F; 
    message[7] = (x >> 8) & 0x0F;
    message[8] = (x >> 4) & 0x0F;
    message[9] = x & 0x0F;

    // y
    message[10] = (y >> 12) & 0x0F; 
    message[11] = (y >> 8) & 0x0F;
    message[12] = (y >> 4) & 0x0F;
    message[13] = y & 0x0F;

    // width
    message[14] = (width >> 12) & 0x0F; 
    message[15] = (width >> 8) & 0x0F;
    message[16] = (width >> 4) & 0x0F;
    message[17] = width & 0x0F;

    // height
    message[18] = (height >> 12) & 0x0F; 
    message[19] = (height >> 8) & 0x0F;
    message[20] = (height >> 4) & 0x0F;
    message[21] = height & 0x0F;

    send(sockfd, message, 22, 0);
}

/**
 * @brief 
 * raws a line starting a point 1 and ending at point 2.  
 * Point 1 is given by the first two parameters, x and y, in that order, and point 2 is 
 * given by the last two parameters, x followed by y. 
 * @param x1 point 1 x coordinate
 * @param y1 point 1 y coordinate
 * @param x2 point 2 x coordinate
 * @param y2 point 2 y coordinate
 */
void GraphicsClient::drawLine(int x1, int y1, int x2, int y2) {
    char message[100];

    //SYNC
    message[0] = 0xFF; 

    // size -> 0011 = 11
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x01;
    message[4] = 0x01; 

    // Draw Line Code
    message[5] = 0x0D;

    //Draw Line Info
    // x1
    message[6] = (x1 >> 12) & 0x0F; 
    message[7] = (x1 >> 8) & 0x0F;
    message[8] = (x1 >> 4) & 0x0F;
    message[9] = x1 & 0x0F;
    // y1
    message[10] = (y1 >> 12) & 0x0F;
    message[11] = (y1 >> 8) & 0x0F;
    message[12] = (y1 >> 4) & 0x0F;
    message[13] = y1 & 0x0F;
    // x2 
    message[14] = (x2 >> 12) & 0x0F;
    message[15] = (x2 >> 8) & 0x0F;
    message[16] = (x2 >> 4) & 0x0F;
    message[17] = x2 & 0x0F;
    // y2
    message[18] = (y2 >> 12) & 0x0F;
    message[19] = (y2 >> 8) & 0x0F;
    message[20] = (y2 >> 4) & 0x0F;
    message[21] = y2 & 0x0F;

    send(sockfd, message, 22, 0);
}

/**
 * @brief 
 * draws a string of characters on the display given by 
 * the last parameter at the position given by the first two parameters, x, y, in that 
 * order. 
 * @param x coordinate
 * @param y coordinate
 * @param str the string drawn
 */
void GraphicsClient::drawstring(int x, int y, std::string str) {
    char message[100];
    int size = 9 + (str.length() * 2);

    //SYNC
    message[0] = 0xFF; 

    //size is dynamic depending on the string length
    message[1] = (size >> 12) & 0x0F;
    message[2] = (size >> 8) & 0x0F;
    message[3] = (size >> 4) & 0x0F;
    message[4] = size & 0x0F; 

    // Draw String Code
    message[5] = 0x05; 

    //Draw String Info
    // x
    message[6] = (x >> 12) & 0x0F;
    message[7] = (x >> 8) & 0x0F;
    message[8] = (x >> 4) & 0x0F;
    message[9] = x & 0x0F;
    // y
    message[10] = (y >> 12) & 0x0F;
    message[11] = (y >> 8) & 0x0F;
    message[12] = (y >> 4) & 0x0F;
    message[13] = y & 0x0F;

    // string
    for(int i = 0; i < str.length() * 2; i+=2) {
        //each character is a byte (2 message bytes to make one character)
        message[i + 14] = (str[i/2] >> 4) & 0x0F;
        message[i+15] = str[i/2] & 0x0F;
    }

    //send message of length size
    send(sockfd, message, size + 5, 0);
}

/**
 * @brief 
 * send the redraw (repaint) signal to the attached graphics server
 */
void GraphicsClient::repaint() {
    char message[100];

    //SYNC
    message[0] = 0xFF; 

    // size -> 0001 = 1
    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01; 

    // Repaint
    message[5] = 0x0C; 

    //send message of length 6
    send(sockfd, message, 6, 0);

}


/**
 * @brief 
 * reads mouse input from the server
 * @param y coordinate
 * @param x coordinate
 * @param height of the 2d array
 * @param width of the 2d array
 * @return int 
 */
int GraphicsClient::getMouseClick(int *y, int *x, int height, int width) {
    int count = 0;
    ioctl(sockfd, FIONREAD, &count);
    if (count != 0) {
        char buffer[100];
        read(sockfd, &buffer, count);
        return readMouseInput(buffer, count, y, x, height, width);
    }
    return 0;
}

/**
 * @brief 
 * interprests the mouse click from the server
 * turns int into x and y and based on the values returns
 * a specific number to symbolize what button was clicked
 * @param message the server message
 * @param size of the message
 * @param yCoord coordinate
 * @param xCoord coordinate
 * @param height of the 2d array
 * @param width of the 2d array
 * @return int 
 */
int GraphicsClient::readMouseInput(char message[100], int size, int *yCoord, int *xCoord, int height, int width) {

    for (int count = 0; count < size / 15; count++) {
        if (message[(count * 15) + 5] != 3 || message[(count * 15) + 6] != 1) {
            
        } else {
            int x1, x2, x3, x4, x, y1, y2, y3, y4, y;

            x1 = message[(count * 15) + 7] & 0x0F;
            x2 = message[(count * 15) + 8] & 0x0F;
            x3 = message[(count * 15) + 9] & 0x0F;
            x4 = message[(count * 15) + 10] & 0x0F;

            x = (x1 << 12) + (x2 << 8) + (x3 << 4) + x4;

            y1 = message[(count * 15) + 11] & 0x0F;
            y2 = message[(count * 15) + 12] & 0x0F;
            y3 = message[(count * 15) + 13] & 0x0F;
            y4 = message[(count * 15) + 14] & 0x0F;

            y = (y1 << 12) + (y2 << 8) + (y3 << 4) + y4;
            // Step
            if(x >= 630 && x <= 690 && y >= 30 && y <= 60) {
                return 1; 
            }
            // Run
            if(x >= 630 && x <= 770 && y >= 30 + 50 && y <= 60 + 50) {
                return 2; 
            }
            // Pause
            if(x >= 630 && x <= 770 && y >= 30 + 100 && y <= 60 + 100) {
                return 3; 
            }
            // Reset
            if(x >= 630 && x <= 770 && y >= 30 + 150 && y <= 60 + 150) {
                return 4; 
            }
            // Random
            if(x >= 630 && x <= 770 && y >= 30 + 200 && y <= 60 + 200) {
                return 5; 
            }
            // Load
            if(x >= 630 && x <= 770 && y >= 30 + 250 && y <= 60 + 250) {
                return 6; 
            }
            // Quit
            if(x >= 630 && x <= 770 && y >= 30 + 300 && y <= 60 + 300) {
                return 7; 
            }
            // Clear
            if(x >= 630 && x <= 770 && y >= 30 + 350 && y <= 60 + 350) {
                return 8; 
            }
            // Set Size 1
            if(x >= 630 && x <= 630 + (140 / 3) && y >= 30 + 450 && y <= 30 + 450 + 30) {
                return 9; 
            }
            // Set Size 2
            if(x >= 630 + 47 && x <= 630 + (140 / 3) + 47 && y >= 30 + 450 && y <= 30 + 450 + 30) {
                return 10; 
            }
            // Set Size 3
            if(x >= 630 + 94 && x <= 630 + (140 / 3) + 94 && y >= 30 + 450 && y <= 30 + 450 + 30) {
                return 11; 
            } 
            if (x >= 0 && x <  (width * pixelSize(height, width)) + (width * gapSize(height, width)) && y >= 0 && y < (height * pixelSize(height, width)) + (height * gapSize(height, width))) {
                *xCoord = (x / (gapSize(height, width) + pixelSize(height, width)));
                *yCoord = (y / (gapSize(height, width) + pixelSize(height, width)));
                return 12;
            }
        }
    }

    
    return 0;

}

/**
 * @brief 
 * private method for manipulating the pixel size
 * @return int 
 */
int GraphicsClient::pixelSize(int height, int width) {
    int m = max(height, width); 
    if(m > 200 && m <= 600) return 1;
    if(m >= 150 & m <= 200) return 2;
    if(m > 50 & m <= 100) return 4;
    if(m > 1 & m <= 50) return 10;
    cout << "Error in pixel size" << endl;
    return 0;
}
/**
 * @brief 
 * private method for manipulating the gap size
 * @return int 
 */
int GraphicsClient::gapSize(int height, int width){
    int m = max(height, width); 
    if(m > 200 && m <= 600) return 0;
    if(m >= 150 & m <= 200) return 1;
    if(m > 50 & m <= 100) return 1;
    if(m > 1 & m <= 50) return 2;
    cout << "Error in gap size" << endl;
    return 0;
}

/**
 * @brief 
 * sends a message to the server
 * to request a file
 */
void GraphicsClient::getFile() {
    char message[100];

    message[0] = 0xFF;

    message[1] = 0x00;
    message[2] = 0x00;
    message[3] = 0x00;
    message[4] = 0x01;

    message[5] = 0x0E;

    send(sockfd, message, 6, 0);
}


/**
 * @brief 
 * gets input from the server of the file name and parsce it into a string
 * @return std::string 
 */
std::string GraphicsClient::getFileName() {
    int count = 0; 
    ioctl(sockfd, FIONREAD, &count);

    char buffer[10000];
    if (count != 0) {
        read(sockfd, &buffer, count);
    }

    std::string filename = "";
    for (int i = 0; i < count - 6; i+=2) {
        filename += ((buffer[i+6] & 0xF) << 4) + (buffer[i+7] & 0xF);
    }
    return filename;
}