#ifndef __VOTE_MACHINE__
#define __VOTE_MACHINE__

#include <unordered_map>

#include "libs.hpp"
#include "candidate.hpp"

namespace vote_system
{
class Vote_machine
{
public:
    Vote_machine(unsigned int machine_ip, unsigned int machine_port);
    ~Vote_machine() = default;
    Vote_machine(const Vote_machine& other) = delete;
    Vote_machine& operator=(const Vote_machine& other) = delete;

    void MakeCandidate(std::string cadidate_name);
    void ShowCandidates();
    void ShowStatistics(); //save to a file?
    // std::unordered_map<Candidate&, int> GetVotes(); //how to I update it in live? 
    void VoteById(unsigned int vote_id);
    std::string& GetVoteMachineDetails() const;
    void ChangeCandidate(unsigned int vote_id, std::string new_candidate);

private:
    // class Candidate;?
    std::unordered_map<unsigned int, Candidate&>& CandidateVotesInit();
    unsigned int m_machine_ip;
    unsigned int m_machine_port;
    std::unordered_map<unsigned int, Candidate&>& candidates_votes;
};
}
#endif //__VOTE_MACHINE__