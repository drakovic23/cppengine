#include "BarData.h"

class IStrategy{
	virtual void onBar (const BarData& bar);
	virtual bool shouldEnterTrade() const = 0;
	virtual bool shouldExitTrade() const = 0;
};
