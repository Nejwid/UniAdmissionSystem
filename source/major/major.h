#include <string>
#include <set>
#include <memory>
#include <queue>

class Candidate;

using namespace::std;

class Major {
protected:
	set<shared_ptr<Candidate>> accepted;
	priority_queue<shared_ptr<Candidate>> candidateQueue;
public:
	void ProcessApplications(int limit);
	void AddCandidate(const shared_ptr<Candidate> C);
	bool IsAccepted(shared_ptr<Candidate> C) const;
	set<shared_ptr<Candidate>> AcceptedList() const;
};
