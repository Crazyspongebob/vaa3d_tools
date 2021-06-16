//------------------------------------------------------------------------------
// Copyright (c) 2019 Hsien-Chi Kuo (Allen Institute)
// All rights reserved.
//------------------------------------------------------------------------------

/*******************************************************************************
*
*  TreeTrimmer class mainly refines and smoothens tree structures. Many of its methods are extended from NeuronGeoGrapher class.
*
*  This class is composited with NeuronStructExplorer class, as it needs NeuronStructExplorer's capability to manage and process neuron tree and neuron segments.
*  The composition is achieved by using a shred_ptr pointing to the "base" NeuronStructExplorer's memory address.
*  This design is due to the possibility of NeuronStructExplorer serving multiple other classes at the same time.
*  TreeGrower is the main interface in NeuronStructNavigator library for "gorwing" trees out of [NeuronSWC]-based signals.
*
********************************************************************************/

#ifndef TREETRIMMER_H
#define TREETRIMMER_H

#include <memory>

#include "integratedDataTypes.h"
#include "NeuronGeoGrapher.h"
#include "NeuronStructExplorer.h"

class TreeTrimmer
{
	friend class Tester;

public:
	/************** Constructors and Basic Data/Function Members ****************/
	TreeTrimmer() { this->sharedExplorerPtr = nullptr; }
	TreeTrimmer(NeuronStructExplorer* baseExplorerPtr) { this->sharedExplorerPtr = make_shared<NeuronStructExplorer*>(baseExplorerPtr); }

	shared_ptr<NeuronStructExplorer*> sharedExplorerPtr;
	/****************************************************************************/


	/************************* Minor Tree Trimming / Refining *************************/
	// Breaks all branches in [inputProfiledTree].
	// Note, if [spikeRemove] == true, any short branches less than [spikeThre] in length will be removed as undesired spikes in stead of being recognized as branches.
	static NeuronTree branchBreak(const profiledTree& inputProfiledTree, double spikeThre = 10, bool spikeRemove = true);

	// Breaks any node-node length that is greater than [distThre].
	static inline NeuronTree treeCut(NeuronTree& inputTree, double distThre = 10);

	// Removes short spikes on segments. The spike length criterion is predefined by users in node count measure.
	// The iterative wrapper should be called to process thoroughly.
	static profiledTree itered_spikeRemoval(const profiledTree& inputProfiledTree, int spikeNodeNum = 3);
	static profiledTree spikeRemoval(const profiledTree& inputProfiledTree, int spikeNodeNum = 3);

	// Removes hooking ends of segments. The criterion is the angle formed within the last 3 nodes.
	// The iterative wrapper should be called in order to remove hooks completely since new angles are being formed while removing sharp angles.
	static profiledTree itered_removeHookingHeadTail(const profiledTree& inputProfiledTree, float radAngleThre);
	static profiledTree removeHookingHeadTail(const profiledTree& inputProiledTree, float radAngleThre);


	profiledTree segSharpAngleSmooth_distThre_3nodes(const profiledTree& inputProfiledTree, const double distThre = 5) const;

	profiledTree itered_segSharpAngleSmooth_lengthDistRatio(const profiledTree& inputProfiledTree, double ratio) const;
private:
	profiledTree segSharpAngleSmooth_lengthDistRatio(const profiledTree& inputProfiledTree, const double ratio) const;	
	/**********************************************************************************/

public:
	map<int, profiledTree> trimmedTree_segEndClusterBased(const profiledTree& inputProfiledTree, const map<int, ImageMarker>& axonGrowingPoints) const;
};

inline NeuronTree TreeTrimmer::treeCut(NeuronTree& inputTree, double distThre)
{
	NeuronTree outputTree;
	for (QList<NeuronSWC>::iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		if (it->parent != -1)
		{
			double x1 = it->x;
			double y1 = it->y;
			double z1 = it->z;
			int paID = it->parent;
			double x2 = inputTree.listNeuron.at(paID - 1).x;
			double y2 = inputTree.listNeuron.at(paID - 1).y;
			double z2 = inputTree.listNeuron.at(paID - 1).z;
			double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + zRATIO * zRATIO * (z1 - z2) * (z1 - z2));
			if (dist > distThre)
			{
				outputTree.listNeuron.push_back(*it);
				(outputTree.listNeuron.end() - 1)->parent = -1;
			}
			else outputTree.listNeuron.push_back(*it);
		}
	}

	return outputTree;
}

#endif