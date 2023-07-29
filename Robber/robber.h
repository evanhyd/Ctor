#ifndef ROBBER_H
#define ROBBER_H

#include <string>

class Robber {
protected:
	int index;

  virtual void MoveToImpl(int index) = 0;
public:
	int GetTileIndex() const;
	void MoveTo(int index);

  	virtual explicit operator std::string() const = 0;

	explicit Robber(int index);
	virtual ~Robber();
};
#endif
