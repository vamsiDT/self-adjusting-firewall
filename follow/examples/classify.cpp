/*
 * follow.cpp
 *
 *  Created on: Jul 8, 2021
 *      Author: vamsi
 */



#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <chrono>
#include <string>
#include <sstream>

#include "./../src/includes/external_includes.h"
#include "./../src/follow/follow.h"
#include "./../src/includes/Assert.h"

#include "./../src/cmd/CommandLine.h"

using namespace std;
using namespace simulator;

int main(int argc, char* argv[]) {

	CommandLine cmd;
	cmd.ParseArgs(argc, argv);

	string rulesetFile = "/home/vamsi/src/phd/self-adjusting-firewall/classbench/db_generator/MyFilters10k";
	 string traceFile = "/home/vamsi/src/phd/self-adjusting-firewall/classbench/db_generator/MyFilters10k_trace";
//	string traceFile = "/home/vamsi/src/phd/self-adjusting-firewall/classbench/db_generator/mytrace";
	string alg = "follow";

	cmd.Get("ruleset",rulesetFile);
	cmd.Get("trace",traceFile);

	vector<Rule> rules = InputReader::ReadFilterFile(rulesetFile);
	vector <Packet> trace = InputReader::ReadPackets(traceFile);

	std::cout << "rulesetSize " << rules.size() << std::endl;
	std::cout << "traceSize " << trace.size() << std::endl;


	if (alg=="follow"){
		follow classifier;
		classifier.CreateClassifier(rules);
		std::cout << "InitDelayms " << classifier.GetInitDelay() << std::endl;

		int count = 0;
		for (auto p:trace){
			classifier.AccessRule(p);
//			if (count > 10){
//				break;
//			}
//			count++;
		}
		std::cout << "Average nodes traversed " << classifier.GetAvgNodesTraversed() << std::endl;
	}

	return 0;
}

