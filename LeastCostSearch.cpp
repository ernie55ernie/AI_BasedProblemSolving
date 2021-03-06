#include "LeastCostSearch.h"

const int MAXTIME = 100000;

LeastCostSearch::LeastCostSearch(void)
{
}


LeastCostSearch::~LeastCostSearch(void)
{
}

void LeastCostSearch::route(){
	stack<MRTInfo> rev;
	int time = 0;
	MRTInfo m;

	// Reverse the stack ti display route.
	while(!btStack.empty()){
		m = btStack.top();
		rev.push(m);
		btStack.pop();
	}

	// Display the route.
	while(!rev.empty()){
			m = rev.top();
			rev.pop();
			cout << m.from << " to ";
			time += m.time;
	}

	cout << m.to << endl;
	cout << "Time is " << time << endl;
}

bool LeastCostSearch::match(string from, string to, int& time){
	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == from &&
			informations[i].to == to && !informations[i].skip){
			informations[i].skip = true;	// prevent reuse
			time = informations[i].time;
			return true;
		}
	}
	return false;	// not found
}

// Given from, find the closest connection.
// Return true if a connection is found,
// and false otherwise.
bool LeastCostSearch::find(string from, MRTInfo& m){
	int pos = -1;
	int time = MAXTIME;

	for(unsigned i = 0; i < informations.size(); i++){
		if(informations[i].from == from && !informations[i].skip){
			// Use the shortest informations.
			if(informations[i].time < time){
				pos = i;
				time = informations[i].time;
			}
		}
	}

	if(pos != -1){
		m = informations[pos];
		informations[pos].skip = true;	// prevent reuse
		return true;
	}
	return false;
}

// Least-cost version
// Determine if there is a route between from and to.
void LeastCostSearch::findroute(string from, string to){
	int time;
	MRTInfo m;

	// See if at destination.
	if(match(from, to, time)){
		btStack.push(MRTInfo(from, to, time));
		return;
	}

	// Try another connection.
	if(find(from, m)){
		btStack.push(MRTInfo(from, to, m.time));
		findroute(m.to, to);
	}else if(!btStack.empty()){
		// Backtrack and try another connection.
		m = btStack.top();
		btStack.pop();
		findroute(m.from, m.to);
	}
}
