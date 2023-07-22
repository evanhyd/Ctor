#ifndef HOUSE_H
#define HOUSE_H
#include "residence.h"

class House : public Residence {
public:
	House(Builder* builder);
	virtual int Points() const override;
};
#endif
