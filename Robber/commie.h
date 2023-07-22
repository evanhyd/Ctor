#ifndef COMMIE_H
#define COMMIE_H
#include "robber.h"

class Commie : public Robber {
public:
	Commie();
	~Commie();
	int GetTileIndex() const override;
	void MoveTo(int tileIndex) override;
};
#endif
