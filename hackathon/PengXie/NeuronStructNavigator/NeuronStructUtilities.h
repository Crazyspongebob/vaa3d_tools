//------------------------------------------------------------------------------
// Copyright (c) 2018 Hsienchi Kuo (Allen Institute, Hanchuan Peng's team)
// All rights reserved.
//------------------------------------------------------------------------------

/*******************************************************************************
*
*  This library provides functionalities for neuron struct operations, such as crop, register, sample, data extraction, etc.
*  NeuronStructUtil class is desinged to take NeuronTree struct as the input and as well output NeuronTree struct for most of the methods.
*  This class intends to operate on the whole neuron struct level, as 'utility' it is called.
*
*  Most NeuronStructUtil class methods are implemented as static functions. The input NeuronTree is always set to be const so that it will not be modified.
*  A typical function call would need at least three input arguments:
*
*		NeuronStructUtil::func(const NeuronTree& inputTree, NeuronTree& outputTree, other input arguments);
*
********************************************************************************/

#ifndef NEURONSTRUCTUTILITIES_H
#define NEURONSTRUCTUTILITIES_H

#include <vector>
#include <string>
#include <fstream>

#include <boost/container/flat_set.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/algorithm/string.hpp>

#include <qlist.h>
#include <qstring.h>
#include <qstringlist.h>

#include "basic_surf_objs.h"
#include "ImgAnalyzer.h"

using namespace std;

#ifndef NODE_TILE_LENGTH
#define NODE_TILE_LENGTH 300
#endif

#ifndef zRATIO // This is the ratio of z resolution to x and y in IVSCC images.
#define zRATIO (0.28 / 0.1144) 
#endif

class NeuronStructUtil
{
public: 
	NeuronStructUtil() {};

	/***************** Basic Neuron Struct Files Operations *****************/
	static void swcSlicer(const NeuronTree& inputTree, vector<NeuronTree>& outputTrees, int thickness = 0);
	static inline void swcCrop(const NeuronTree& inputTree, NeuronTree& outputTree, float xlb, float xhb, float ylb, float yhb, float zlb, float zhb);
	static inline void swcDownSample(const NeuronTree& inputTree, NeuronTree& outputTree, int factor, bool shrink);

	static inline NeuronTree swcScale(const NeuronTree& inputTree, float xScale, float yScale, float zScale);
	static inline NeuronTree swcShift(const NeuronTree& inputTree, float xShift, float yShift, float zShift);
	static NeuronTree swcRegister(NeuronTree& inputTree, const NeuronTree& refTree);
	
	static map<int, QList<NeuronSWC>> swcSplitByType(const NeuronTree& inputTree);
	static NeuronTree swcSubtraction(const NeuronTree& targetTree, const NeuronTree& refTree, int type = 0);
	/************************************************************************/
	
	/***************** Neuron Struct Profiling Methods *****************/
	static inline void nodeTileMapGen(const NeuronTree& inputTree, map<string, vector<int>>& nodeTileMap, float nodeTileLength = NODE_TILE_LENGTH);
	static inline void nodeTileMapGen(const NeuronTree& inputTree, map<string, vector<NeuronSWC>>& nodeTileMap, float nodeTileLength = NODE_TILE_LENGTH);
	static inline void nodeTileMapGen(const NeuronTree& inputTree, boost::container::flat_map<string, vector<int>>& nodeTileMap, float nodeTileLength = NODE_TILE_LENGTH);
	static inline void nodeTileMapGen(const NeuronTree& inputTree, boost::container::flat_map<string, QList<NeuronSWC>>& nodeTileMap, float nodeTileLength = NODE_TILE_LENGTH);
	static inline void nodeTileMapGen(const NeuronTree& inputTree, boost::container::flat_map<string, vector<NeuronSWC>>& nodeTileMap, float nodeTileLength = NODE_TILE_LENGTH);
	static inline void nodeTileMapGen(const QList<NeuronSWC>& inputNodeList, boost::container::flat_map<string, vector<NeuronSWC>>& nodeTileMap, float nodeTileLength = NODE_TILE_LENGTH);

	static QList<NeuronSWC> removeRednNode(const NeuronTree& inputTree);
	static NeuronTree swcZclenUP(const NeuronTree& inputTree, float zThre = 10);
	static inline void node2loc_node2childLocMap(const QList<NeuronSWC>& inputNodeList, map<int, size_t>& nodeLocMap, map<int, vector<size_t>>& node2childLocMap);
	static map<string, float> selfNodeDist(const QList<NeuronSWC>& inputNodeList);
	/*******************************************************************/

	/***************** Inter-SWC Comparison/Analysis *****************/
	static NeuronTree swcIdentityCompare(const NeuronTree& subjectTree, const NeuronTree& refTree, float distThre, float nodeTileLength = NODE_TILE_LENGTH);
	/*****************************************************************/

	/***************** SWC to ImgAnalyzer::connectedComponent *****************/
	vector<connectedComponent> swc2signal2DBlobs(const NeuronTree& inputTree);
	vector<connectedComponent> swc2signal3DBlobs(const NeuronTree& inputTree);
	vector<connectedComponent> merge2DConnComponent(const vector<connectedComponent>& inputConnCompList);
	/**************************************************************************/

	/***************** Neuron Struct Clustering Method *****************/
	static vector<connectedComponent> swc2clusters_distance(const NeuronTree& inputTree, float dist = 30);
	/*******************************************************************/

	/***************** Sampling Methods for Simulated Volumetric Patch Generation *****************/
	static void sigNode_Gen(const NeuronTree& inputTree, NeuronTree& outputTree, float ratio, float distance);
	static void bkgNode_Gen(const NeuronTree& inputTree, NeuronTree& outputTree, int dims[], float ratio, float distance);
	static void bkgNode_Gen_somaArea(const NeuronTree& inputTree, NeuronTree& outputTree, int xLength, int yLength, int zLength, float ratio, float distance);
	/**********************************************************************************************/

	/***************** Miscellaneious *****************/
	static inline void linkerFileGen_forSWC(string swcFullFileName);
	/**************************************************/
};

inline NeuronTree NeuronStructUtil::swcScale(const NeuronTree& inputTree, float xScale, float yScale, float zScale)
{
	NeuronTree outputTree;
	for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		NeuronSWC newNode;
		newNode = *it;
		newNode.x = it->x / xScale;
		newNode.y = it->y / yScale;
		newNode.z = it->z / zScale;
		outputTree.listNeuron.push_back(newNode);
	}

	return outputTree;
}

inline NeuronTree NeuronStructUtil::swcShift(const NeuronTree& inputTree, float xShift, float yShift, float zShift)
{
	NeuronTree outputTree;
	for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		NeuronSWC newNode;
		newNode = *it;
		newNode.x = it->x + xShift;
		newNode.y = it->y + yShift;
		newNode.z = it->z + zShift;
		outputTree.listNeuron.push_back(newNode);
	}

	return outputTree;
}

inline void NeuronStructUtil::swcCrop(const NeuronTree& inputTree, NeuronTree& outputTree, float xlb, float xhb, float ylb, float yhb, float zlb, float zhb)
{
	if (zlb == 0 && zhb == 0)
	{
		for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
		{
			if (it->x < xlb || it->x > xhb || it->y < ylb || it->y > yhb) continue;
			else
			{
				NeuronSWC newNode;
				newNode.x = it->x - (xlb - 1);
				newNode.y = it->y - (ylb - 1);
				newNode.z = it->z;
				newNode.type = it->type;
				newNode.n = it->n;
				newNode.parent = it->parent;
				outputTree.listNeuron.push_back(newNode);
			}
		}
	}
}

void NeuronStructUtil::swcDownSample(const NeuronTree& inputTree, NeuronTree& outputTree, int factor, bool shrink)
{
	QList<NeuronSWC> inputList = inputTree.listNeuron;
	outputTree.listNeuron.clear();
	for (QList<NeuronSWC>::iterator it = inputList.begin(); it != inputList.end(); ++it)
	{
		if (int(it->z) % factor == 0 && int(it->x) % factor == 0 && int(it->y) % factor == 0) 
			outputTree.listNeuron.push_back(*it);
	}

	if (shrink)
	{
		for (QList<NeuronSWC>::iterator it = outputTree.listNeuron.begin(); it != outputTree.listNeuron.end(); ++it)
		{
			it->x = it->x / 2;
			it->y = it->y / 2;
			it->z = it->z / 2;
		}
	}
}

inline void NeuronStructUtil::nodeTileMapGen(const NeuronTree& inputTree, map<string, vector<int>>& nodeTileMap, float nodeTileLength)
{
	for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		string xLabel = to_string(int(it->x / nodeTileLength));
		string yLabel = to_string(int(it->y / nodeTileLength));
		string zLabel = to_string(int(it->z / (nodeTileLength / zRATIO)));
		string keyLabel = xLabel + "_" + yLabel + "_" + zLabel;
		if (nodeTileMap.find(keyLabel) != nodeTileMap.end()) nodeTileMap[keyLabel].push_back(it->n);
		else
		{
			vector<int> newSet;
			newSet.push_back(it->n);
			nodeTileMap.insert(pair<string, vector<int>>(keyLabel, newSet));
		}
	}
}

inline void NeuronStructUtil::nodeTileMapGen(const NeuronTree& inputTree, map<string, vector<NeuronSWC>>& nodeTileMap, float nodeTileLength)
{
	for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		string xLabel = to_string(int(it->x / nodeTileLength));
		string yLabel = to_string(int(it->y / nodeTileLength));
		string zLabel = to_string(int(it->z / (nodeTileLength / zRATIO)));
		string keyLabel = xLabel + "_" + yLabel + "_" + zLabel;
		if (nodeTileMap.find(keyLabel) != nodeTileMap.end()) nodeTileMap[keyLabel].push_back(*it);
		else
		{
			vector<NeuronSWC> newSet;
			newSet.push_back(*it);
			nodeTileMap.insert(pair<string, vector<NeuronSWC>>(keyLabel, newSet));
		}
	}
}

inline void NeuronStructUtil::nodeTileMapGen(const NeuronTree& inputTree, boost::container::flat_map<string, vector<int>>& nodeTileMap, float nodeTileLength)
{
	for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		string xLabel = to_string(int(it->x / nodeTileLength));
		string yLabel = to_string(int(it->y / nodeTileLength));
		string zLabel = to_string(int(it->z / (nodeTileLength / zRATIO)));
		string keyLabel = xLabel + "_" + yLabel + "_" + zLabel;
		if (nodeTileMap.find(keyLabel) != nodeTileMap.end()) nodeTileMap[keyLabel].push_back(it->n);
		else
		{
			vector<int> newSet;
			newSet.push_back(it->n);
			nodeTileMap.insert(pair<string, vector<int>>(keyLabel, newSet));
		}
	}
}

inline void NeuronStructUtil::nodeTileMapGen(const NeuronTree& inputTree, boost::container::flat_map<string, QList<NeuronSWC>>& nodeTileMap, float nodeTileLength)
{
	for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		string xLabel = to_string(int(it->x / nodeTileLength));
		string yLabel = to_string(int(it->y / nodeTileLength));
		string zLabel = to_string(int(it->z / (nodeTileLength / zRATIO)));
		string keyLabel = xLabel + "_" + yLabel + "_" + zLabel;
		if (nodeTileMap.find(keyLabel) != nodeTileMap.end()) nodeTileMap[keyLabel].push_back(*it);
		else
		{
			QList<NeuronSWC> newSet;
			newSet.push_back(*it);
			nodeTileMap.insert(pair<string, QList<NeuronSWC>>(keyLabel, newSet));
		}
	}
}

inline void NeuronStructUtil::nodeTileMapGen(const NeuronTree& inputTree, boost::container::flat_map<string, vector<NeuronSWC>>& nodeTileMap, float nodeTileLength)
{
	for (QList<NeuronSWC>::const_iterator it = inputTree.listNeuron.begin(); it != inputTree.listNeuron.end(); ++it)
	{
		string xLabel = to_string(int(it->x / nodeTileLength));
		string yLabel = to_string(int(it->y / nodeTileLength));
		string zLabel = to_string(int(it->z / (nodeTileLength / zRATIO)));
		string keyLabel = xLabel + "_" + yLabel + "_" + zLabel;
		if (nodeTileMap.find(keyLabel) != nodeTileMap.end()) nodeTileMap[keyLabel].push_back(*it);
		else
		{
			vector<NeuronSWC> newSet;
			newSet.push_back(*it);
			nodeTileMap.insert(pair<string, vector<NeuronSWC>>(keyLabel, newSet));
		}
	}
}

inline void NeuronStructUtil::nodeTileMapGen(const QList<NeuronSWC>& inputNodeList, boost::container::flat_map<string, vector<NeuronSWC>>& nodeTileMap, float nodeTileLength)
{
	for (QList<NeuronSWC>::const_iterator it = inputNodeList.begin(); it != inputNodeList.end(); ++it)
	{
		string xLabel = to_string(int(it->x / nodeTileLength));
		string yLabel = to_string(int(it->y / nodeTileLength));
		string zLabel = to_string(int(it->z / (nodeTileLength / zRATIO)));
		string keyLabel = xLabel + "_" + yLabel + "_" + zLabel;
		if (nodeTileMap.find(keyLabel) != nodeTileMap.end()) nodeTileMap[keyLabel].push_back(*it);
		else
		{
			vector<NeuronSWC> newSet;
			newSet.push_back(*it);
			nodeTileMap.insert(pair<string, vector<NeuronSWC>>(keyLabel, newSet));
		}
	}
}

inline void NeuronStructUtil::node2loc_node2childLocMap(const QList<NeuronSWC>& inputNodeList, map<int, size_t>& nodeLocMap, map<int, vector<size_t>>& node2childLocMap)
{
	// This method profiles node-location node-child_location of a given NeuronTree.
	// In current implementation, a single node will carry a node.n-vector<size_t> pair in node2childLocMap where its vector<size> is empty.
	// However, any tip node will not have an entry in node2childLocMap.

	nodeLocMap.clear();
	for (QList<NeuronSWC>::const_iterator it = inputNodeList.begin(); it != inputNodeList.end(); ++it)
		nodeLocMap.insert(pair<int, size_t>(it->n, (it - inputNodeList.begin())));
	//cout << " Node - Locations mapping done. size: " << nodeLocMap.size() << endl;

	node2childLocMap.clear();
	for (QList<NeuronSWC>::const_iterator it = inputNodeList.begin(); it != inputNodeList.end(); ++it)
	{
		int paID = it->parent;
		if (paID == -1)
		{
			vector<size_t> childSet;
			childSet.clear();
			node2childLocMap.insert(pair<int, vector<size_t>>(it->n, childSet));
		}
		else
		{
			if (node2childLocMap.find(paID) != node2childLocMap.end())
			{
				node2childLocMap[paID].push_back(size_t(it - inputNodeList.begin()));
				//cout << paID << " " << size_t(it - inputNodeList.begin()) << endl;
			}
			else
			{
				vector<size_t> childSet;
				childSet.clear();
				childSet.push_back(size_t(it - inputNodeList.begin()));
				node2childLocMap.insert(pair<int, vector<size_t>>(paID, childSet));
				//cout << paID << " " << size_t(it - inputNodeList.begin()) << endl;
			}
		}
	}
	//cout << " node - Child location mapping done. size: " << node2childLocMap.size() << endl;
}

inline void NeuronStructUtil::linkerFileGen_forSWC(string swcFullFileName)
{
	vector<string> swcFullNameParse;
	boost::split(swcFullNameParse, swcFullFileName, boost::is_any_of("\\"));
	string swcName = swcFullNameParse.back();
	vector<string> swcBaseNameParse;
	boost::split(swcBaseNameParse, swcName, boost::is_any_of("."));
	string swcBaseName = swcBaseNameParse.front();

	string rootPath;
	for (vector<string>::iterator it = swcFullNameParse.begin(); it != swcFullNameParse.end() - 1; ++it)
		rootPath = rootPath + *it + "/";
	string anoFullName = rootPath + swcBaseName + ".ano";

	ofstream outputFile(anoFullName.c_str());
	outputFile << "SWCFILE=" << swcName << endl;
	outputFile.close();
}

#endif 
