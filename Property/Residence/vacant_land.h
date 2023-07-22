#ifndef VACANT_LAND_H
#define VACANT_LAND_H
#include "residence.h"

class Builder;

class VacantLand : public Residence {
public:
	VacantLand(Builder* builder);
	virtual int Points() const override;
};
#endif
