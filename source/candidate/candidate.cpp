#include "candidate.h"


Candidate::Candidate(string name, int score, vector<shared_ptr<Major>> vec) : name(name), score(score) {
	if (vec.size() > 2) {
		vec.resize(2);
	}
	for (auto& it : vec) {
		if (it) {
			applications[it] = false;
		}
	}
}

int Candidate::GetScore() const {
	return this->score;
}

string Candidate::GetName() const {
	return this->name;
}

bool Candidate::operator<(const shared_ptr<Candidate> other) {
	return this->score < other->score;
}

bool Candidate::operator==(const shared_ptr<Candidate> other) {
	return this->score == other->score;
}