Goal Oriented Action Planning:

Because it is not a very popular technique used in AI, it can be hard to find resources or ready-made frameworks that facilitate the implementation of a Goal Oriented Action Planning system. Our framework aims to fill in that gap with a simple and intuitive system that can help anyone have complex AI behavior without the trouble of going through implementing it from scratch. 

We are relying on the component based architecture of modern game engines to structure our classes. The classes we built are aimed at being components attached to a main game object which is the agent. These classes will interact with each other through the base game object and are for the most part dependent on each other.

Our framework is divided into 4 different base classes which are the building blocks of the GOAP agents’ behaviors. In this section we are going to explain the use of each class and tie in all of the systems together. The classes are as follows: 
	1) AIAgent
	2) BaseGoap
	3) Action 
	4) Planner 
(Classes themselves are named differently in our code because of the Unreal Engine naming conventions. Action is UAction etc…)

A short explanation of each class:

1)AIAgent:
The AIAgent class is the glue that ties in all of the different classes together. This is a simple class that gives the Agent a very simple finite state machine. This class 	is not meant to be modified or extended. The state machine has 3 different states 

a) Idle state; the state in which the agent is planning his next moves. This agent will not be spending a lot of time in this state unless there are no plans that can satisfy his current goal.
b) MoveTo state; as the name indicates in this state, the agent will move to a desired location in case the next action he needs to take requires him to. 
c) Action state; this is where the agent will spend most of his time. This state is the most flexible one since it’­­­s up to the developer to decide what behaviors go into the actions

2)BaseGoap: 
The BaseGoap class aims at abstracting the different AI personalities. Whenever a
developer needs to create a new type of character, say a Guard NPC, she would extend this class and add the appropriate behaviors to it. 
This class has pure virtual functions that need to be implemented by any class that extends it.
 
a) GetWorldState which returns a map of string to Boolean to indicate this agent’s current world state (for example “enemies_around”,true if the guard can see enemies)

b) GetGoalState which returns a map of string to Boolean values to indicate what this agent is trying to achieve. (for example “enemies_around”,false which means this guard’s goal is to eliminate all enemies)

c) FailedToFindPlan which is called by the FSM in case a plan could not be found. This function is used to add in custom behavior for each NPC profile to have a unique and flexible way of dealing with the world when no plan can be found. It can be used to alter the agent’s current goal. 

d) PlanFound and ReachedGoal are less important functions that can be used to add in custom animations or feedback to the world when a plan is found or a goal is reached by an agent.

e) PlanAborted is called whenever something in the world prevents the agent to carry on with his current plan. The appropriate action that was stopped is also sent to this function for convenience.
 
f) MoveAgent is the function called during the MoveTo state in the FSM.
										
3) Action:
At initialization, the AI Agent class gets a list of Actions attached to the same game object that is using it and creates a list of available Actions for this agent. The Action class is also an abstract class that would need to be extended for each different action that the developer wants to define in their game. 

The goal of the AI Agent is to find the plan with the lowest total cost. This is where each action’s individual cost comes in. When extending this class, the developer needs to override the functions to return the appropriate values each action.

4) Planner:
The planner class is the main logic that goes inside the agent’s code to figure out a 	plan which takes the current world’s state and turns it into the desired state. 

This class does not need to be unique for each agent because the method of 	searching for a plan does not affect the desired behavior. It is called in every agent’s Idle state.

The search method used in our framework currently does a recursive brute-force search of all possible plans (if available) and returns only the one with the lowest cost. This class can be edited or extended to change the method of searching. 
One such method could be using the A* to find the lowest cost plan very efficiently as implemented by Monolith in their game F.E.A.R. It is up to the developer to choose whichever search method to use for planning


