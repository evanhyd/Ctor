#ifndef GEESE_H
#define GEESE_H
#include "robber.h"

class Geese : public Robber {
public:
	Geese();
	~Geese();
	int GetTileIndex() const override;
	void MoveTo(int tileIndex) override;
};
#endif
