#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory {
	int brick;
	int energy;
	int glass;
	int heat;
	int wifi;
	
public:
	constexpr Inventory(int brick, int energy, int glass, int heat, int wifi);
	
	int GetTotal() const;
	bool TrySpend(const Inventory& other);
	void Gain(const Inventory& other);
};

#endif
