#ifndef DEFAULT_LAYOUT_H
#define DEFAULT_LAYOUT_H

#include <vector>
#include "layout.h"

class DefaultLayout : public Layout {
public:
	DefaultLayout() = default; 

	bool CanBuildRoad(int index) override;
	bool CanBuildRes(int index) override;
	bool BuildRoad(int index) override;
	bool BuildRes(int index) override;
	void MoveRobber(int index) override;
};
#endif
