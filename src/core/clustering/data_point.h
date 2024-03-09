#pragma once

class DataPoint {
public:
    DataPoint();
    DataPoint(int xpos, int ypos, int clusterIdx = -1);
    
    ~DataPoint();
    
    void setPos(int xpos, int ypos);
    void setXpos(int xpos);
    void setYpos(int ypos);
    void setRandomPos(int xmax, int ymax);

    void setClusterIdx(int cidx);

    int getXpos() const;
    int getYpos() const;
    int getClusterIdx() const;

private:
    int xpos_ = 0;
    int ypos_ = 0;
    int clusterIdx_ = -1;
};
