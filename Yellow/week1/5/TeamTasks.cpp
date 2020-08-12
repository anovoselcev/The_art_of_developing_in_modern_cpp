#include <iostream>
#include<map>
#include<tuple>
#include<string>
using namespace std;


class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const{
	  return team.at(person);
  }
  void AddNewTask(const string& person){
	  team[person][TaskStatus::NEW]++;
  }
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
	  TasksInfo update,old=team[person];
	  old.erase(TaskStatus::DONE);
	  while((task_count>0)&&(team[person][TaskStatus::NEW]>0)){
		  team[person][TaskStatus::NEW]--;
		  team[person][TaskStatus::IN_PROGRESS]++;
		  update[TaskStatus::IN_PROGRESS]++;
		  old[TaskStatus::NEW]--;
		  task_count--;
	  }
	  if(team[person][TaskStatus::NEW]==0)
		  team[person].erase(TaskStatus::NEW);
	  if(old[TaskStatus::NEW]==0)
		  old.erase(TaskStatus::NEW);
	  while((task_count>0)&&(team[person][TaskStatus::IN_PROGRESS]-update[TaskStatus::IN_PROGRESS]>0)){
		  team[person][TaskStatus::IN_PROGRESS]--;
		  team[person][TaskStatus::TESTING]++;
		  update[TaskStatus::TESTING]++;
		  old[TaskStatus::IN_PROGRESS]--;
		  task_count--;
	  }
	  if(team[person][TaskStatus::IN_PROGRESS]==0)
		  team[person].erase(TaskStatus::IN_PROGRESS);
	  if(old[TaskStatus::IN_PROGRESS]==0)
		  old.erase(TaskStatus::IN_PROGRESS);
	  while((task_count>0)&&(team[person][TaskStatus::TESTING]-update[TaskStatus::TESTING]>0)){
		  team[person][TaskStatus::TESTING]--;
		  team[person][TaskStatus::DONE]++;
		  update[TaskStatus::DONE]++;
		  old[TaskStatus::TESTING]--;
		  task_count--;
	 }
	  if(team[person][TaskStatus::TESTING]==0)
		  team[person].erase(TaskStatus::TESTING);
	  if(old[TaskStatus::TESTING]==0)
		  old.erase(TaskStatus::TESTING);
	  return make_tuple(update,old);
  }
private:
  map<string,TasksInfo> team;
};

