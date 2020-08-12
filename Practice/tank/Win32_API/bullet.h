#pragma once
class bullet {
public:
	POINT createLoc;
	POINT nowLoc;
	float speed;
	float angle;
	bool created = false;

	bullet() {};
	~bullet() {};
};