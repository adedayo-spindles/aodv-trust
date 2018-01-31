//#include "stdafx.h"
#include "TrustLevelClassifier.h"
#include "RecommendationTableEntry.h"
#include "TestValueGenerator.h"
#include <vector>
#include <iostream>
#include "BackupTable.h"
#include "IndTrustCal.h"
#include "TrustTableEntry.h"
#include "DirTrustCal.h"
#include "Node.h"
#include "TestValueGenerator.h"
#include "TrustLevelClassifier.h"
#include "Spiral.h"

#include <iostream>

namespace ns3
{
namespace aodv
{

TrustLevelClassifier::TrustLevelClassifier()
{
}


void TrustLevelClassifier::identifyTrustLevel(TrustTable* trustTable)
{
	double Threshold_trust = 0.5;
	double Threshold_trustWorthy = 0.8;
	double Threshold_selfish = 0.3;

	std::vector<TrustTableEntry>& node_entry_vector = trustTable->getTrustTableEntries();
	double node_GT;

	for (TrustTableEntry& node : node_entry_vector) {

		node_GT = node.getGlobalTrust();

		std::cout << "Trust level: " << node.getTrustLevel() << std::endl;
		std::cout << "Indirect Trust: " << node.getIndirectTrust() << std::endl;

		if (node_GT > Threshold_trust)
		{
			if (node_GT > Threshold_trustWorthy)
			{
				node.setTrustLevel(1);
			}
			else
			{
				node.setTrustLevel(2);
			}
		}

		else
		{
			if (node_GT > Threshold_selfish)
			{
				node.setTrustLevel(3);

				//double	reduction_factor = calculateReductionFactor(node.getInteractionCount(), node.getGlobalTrust());


				//RecommendationTable* recTable = TestValueGenerator::getDummyRecommendationTableByTrustTable(trustTable);

				//std::vector<RecommendationTableEntry> rec_entry_vector = recTable->getRecommendationTableEntries();
				//std::vector<string>* recommendingNodesList;

				//for (vector<RecommendationTableEntry>::iterator it = rec_entry_vector.begin(); it != rec_entry_vector.end(); it++) {
				//	

				//	//for (vector<RecommendationTableEntry>::iterator recNode = recommendingNodesList.begin(); recNode != recommendingNodesList.end(); recNode++)
				//	//{
				//	//	recNode->
				//	//}
				//}

//recalculateIndirectTrust(it->getIndirectTrust(), reduction_factor);
			}
			else
			{
				//call spiral model method
				Spiral model;
				double *past_global_trust_range;
				past_global_trust_range = model.getMinMaxTrust(BackupTable::getInstance()->getTrustList());

				model.addMaliciousCategory(past_global_trust_range, trustTable);
			}
		}

		std::cout << "Trust level: " << node.getTrustLevel() << std::endl;
		std::cout << "Indirect Trust: " << node.getIndirectTrust() << std::endl;
	}
}


double TrustLevelClassifier::calculateReductionFactor(int interactions, double globalTrust)
{
	double reductionFactor;
	reductionFactor = globalTrust / interactions;

	return reductionFactor;
}


double TrustLevelClassifier::recalculateIndirectTrust(double indirectTrust, double reductionFactor)
{
	indirectTrust = indirectTrust - reductionFactor;
	//update global trust
	return indirectTrust;
}

TrustLevelClassifier::~TrustLevelClassifier()
{
}

}
}