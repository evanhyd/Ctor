#ifndef ROBBER_H
#define ROBBER_H

class Robber {
protected:
	int tileIndex;

  virtual void MoveToImpl(int tileIndex) = 0;
public:
	int GetTileIndex() const;
	void MoveTo(int tileIndex);

	explicit Robber(int tileIndex);
	virtual ~Robber();
};
#endif
