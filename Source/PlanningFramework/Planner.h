// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include <queue>
#include <unordered_map>
#include <set>
#include <list>
/**
 * 
 */

class UAction;
class AActor;

class PLANNINGFRAMEWORK_API Planner
{
public:
	class Node
	{

	public:
		Node(Node* p, float icost, std::unordered_map<std::string, bool> istate, UAction* a) : parent(p), cost(icost), state(istate), action(a)
		{
		}
		~Node();
		Node* parent;
		float cost;
		std::unordered_map<std::string, bool> state;
		UAction* action;
	};

	Planner();
	~Planner();
	std::queue<UAction*> Plan(AActor* agent, std::set<UAction*> actions, 
		std::unordered_map<std::string, bool> world_state,
		std::unordered_map<std::string, bool> goal);
	bool Search(Node* parent, std::list<Node*>& leaves, std::set<UAction*> actions, std::unordered_map<std::string, bool>& goal);
	bool SatisfiesPreconditions(const std::unordered_map<std::string, bool>& preconditions, const std::unordered_map<std::string, bool>& state);
	std::unordered_map<std::string, bool> UpdateState(std::unordered_map<std::string, bool> current_state, std::unordered_map<std::string, bool> changes);
	
};
