#include "major.h"
#include "candidate.h"

bool Major::IsAccepted(shared_ptr < Candidate> C) const {
	return this->accepted.contains(C);
}

void Major::AddCandidate(const shared_ptr<Candidate> C) {
	this->candidateQueue.push(C);
}

void Major::ProcessApplications(int limit) {
	if (candidateQueue.empty()) return;
	int last = 0;
	for (int i = 0; i < limit; i++) {
		if (!candidateQueue.empty()) {
			accepted.insert(candidateQueue.top());
			last = candidateQueue.top()->GetScore();
			candidateQueue.pop();
		}
		else {
			break;
		}
	}
	while (!candidateQueue.empty() && last == candidateQueue.top()->GetScore()) { // if theres more candidates with the same score as the last one's
		accepted.insert(candidateQueue.top());
		candidateQueue.pop();
	}
}

set<shared_ptr<Candidate>> Major::AcceptedList() const {
	return this->accepted;
}