#include <string>
#include <memory>
#include <map>
#include <vector>

class Major;

using namespace::std;

class Candidate {
protected:
	string name;
	int score;
	map<shared_ptr<Major>, bool> applications;
public:
	Candidate(string name, int score, vector<shared_ptr<Major>> vec);
	bool operator<(const shared_ptr<Candidate> other);
	bool operator==(const shared_ptr<Candidate> other);
	int GetScore() const;
	string GetName() const;

};