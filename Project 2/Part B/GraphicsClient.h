#ifndef GRAPHICSCLIENT_H
#define GRAPHICSCLIENT_H

class GraphicsClient {
    private:
        int sockfd;
        std::string url;
        int portNum;
        int pixelSize(int, int);
        int gapSize(int, int);

    public:
        GraphicsClient(std::string, int); //Constructor
        GraphicsClient(const GraphicsClient &); //Copy Constructor
        ~GraphicsClient(); //Destructor
        const GraphicsClient & operator=(const GraphicsClient &); //operator =
        void setBackgroundColor(int, int, int);
        void setDrawingColor(int, int, int);
        void clear();
        void setPixel(int, int, int, int, int);
        void drawRectangle(int, int, int, int);
        void fillRectangle(int, int, int, int);
        void clearRectangle(int, int, int, int);
        void drawOval(int, int, int, int);
        void fillOval(int, int, int, int);
        void drawLine(int, int, int, int);
        void drawstring(int, int, std::string);
        void repaint(); 
        int getMouseClick(int *, int *, int, int);
        int readMouseInput(char [100], int, int *, int *, int, int);
        void getFile();
        std::string getFileName();
};

#endif