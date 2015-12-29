// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanningFramework.h"
#include "Planner.h"
#include "Action.h"
#include <list>

Planner::Planner()
{
}

Planner::~Planner()
{
}

std::queue<UAction*> Planner::Plan(AActor* agent, std::set<UAction*> actions,
	std::unordered_map<std::string, bool> world_state,
	std::unordered_map<std::string, bool> goal)
{
	std::queue<UAction*> theplan;
	std::set<UAction*> useable_actions;

	if (SatisfiesPreconditions(goal, world_state))
	{
		//goal already satisfied
		return theplan;
	}

	for (auto a : actions) {
		a->ResetAction();
		if (a->CheckProceduralPrecondition(agent))
			useable_actions.insert(a);
	}

	std::list<Node*> plans;
	Node* start = new Node(NULL, 0, world_state, NULL);

	bool success = Search(start,plans,useable_actions,goal);

	if (!success)
	{
		return theplan;
	}
	Node* cheapest = NULL;
	for (auto n : plans)
	{
		if (cheapest == NULL)
			cheapest = n;
		else
		if (n->cost < cheapest->cost)
			cheapest = n;
	}
	std::list<Node*> best_plan;
	Node* n = cheapest;
	while (n != NULL)
	{
		if (n->action != NULL)
		{
			best_plan.insert(best_plan.begin(), n);
		}
		n = n->parent;
	}

	for (auto i : best_plan)
		theplan.push(i->action);

	return theplan;
}

bool Planner::SatisfiesPreconditions(const std::unordered_map<std::string, bool>& preconditions,const std::unordered_map<std::string, bool>& state)
{
	for (auto i : preconditions)
	{
		bool match = false;
		for (auto j : state)
		{
			if (i.first == j.first)
			{
				if (i.second == j.second)
				{
					match = true;
					break;
				}
			}
		}
		if (!match)
			return false;
	}
	
	return true;
}

bool Planner::Search(Node* parent, std::list<Node*>& leaves, std::set<UAction*> actions, std::unordered_map<std::string, bool>& goal)
{
	bool found = false;
	for (auto a : actions)
	{
		if (SatisfiesPreconditions(a->preconditions, parent->state))
		{
			std::unordered_map<std::string, bool> new_state = UpdateState(parent->state, a->effects);
			Node* node = new Node(parent, parent->cost + a->cost, new_state, a);
			if (SatisfiesPreconditions(goal, new_state))
			{
				leaves.push_back(node);
				found = true;
			}
			else
			{
				std::set<UAction*> remaining = actions;
				remaining.erase(a);
				bool f = Search(node, leaves, remaining, goal);
				if (f)
					found = true;
			}
		}
	}
	return found;
}

std::unordered_map<std::string, bool> Planner::UpdateState(std::unordered_map<std::string, bool> current_state, std::unordered_map<std::string, bool> changes)
{
	std::unordered_map<std::string, bool> new_state = current_state;

	for (auto i : changes)
	{
		new_state[i.first] = i.second;
	}

	return new_state;
}