#pragma once
#include "TrustTable.h"

namespace ns3
{
namespace aodv
{

class MetaDataToolKit
{
private:
	int rreq;
	int rply;
	int hello;
	int err;
	int noOfDataPacketsForward;
	int noOfDataPacketsReceived;
	int noOfControlPackets;
	int noOfDataPackets;
public:
	MetaDataToolKit();
	void incRREQ();
	void incRPLY();
	void incERR();
	void incHELLO();
	void incNDF();
	void incNDR();
	int getHELLO();
	int getERR();
	int getRREQ();
	int getRPLY();
	int getNDF();
	int getNDR();
    TrustTable* getTrustTableEntries();


	~MetaDataToolKit();
};

}
}
