#pragma once

class DataPoint {
public:
    DataPoint();
    DataPoint(int xpos, int ypos);
    ~DataPoint();
    
    void setPos(int xpos, int ypos);
    void setXpos(int xpos);
    void setYpos(int ypos);
    int getXpos() const;
    int getYpos() const;

private:
    int xpos_ = 0;
    int ypos_ = 0;
};
