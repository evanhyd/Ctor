#ifndef ROBBER_H
#define ROBBER_H
class Robber {
public:
	Robber();
	virtual ~Robber();
	virtual int GetTileIndex() const = 0;
	virtual void MoveTo(int tileIndex) = 0;
protected:
	int tileIndex;
};
#endif
