#ifndef TOWER_H
#define TOWER_H
#include "residence.h"

class Tower : public Residence {
public:
	Tower(Builder* builder);
	virtual int Points() const override;
};
#endif
