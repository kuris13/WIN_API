#pragma once
class bullet {
public:
	POINT createLoc;
	POINT nowLoc;
	int speed;
	float angle;
	int bulletLengthX = 0;

	int bulletLengthY = 0;
	bool created = false;


	bool turnY = false;
	bool turnX = false;
	
	int turnCount = 0;
	bullet() {};
	~bullet() {};
};