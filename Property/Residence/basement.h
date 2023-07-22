#ifndef BASEMENT_H
#define BASEMENT_H
#include "residence.h"

class Basement : public Residence {
public:
	Basement(Builder* builder);

	virtual int Points() const override;
};
#endif
