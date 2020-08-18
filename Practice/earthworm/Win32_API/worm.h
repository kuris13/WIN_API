#pragma once
class worm {
private:
	
	


public:
	POINT loc;
	int radius;
	int bodySize;
	float angle;
	int speed;
	vector<POINT> bodyLoc;
	vector<float> bodyAngle;
	void setLoc(POINT loc) { this->loc = loc; };
};