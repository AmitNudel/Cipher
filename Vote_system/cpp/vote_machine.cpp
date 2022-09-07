
#include "vote_machine.hpp"
#include "libs.hpp"

namespace vote_system
{

Vote_machine::Vote_machine(unsigned int machine_ip,unsigned int machine_port)
:m_machine_ip(machine_ip), m_machine_port(machine_port), candidates_votes(CandidateVotesInit())
{

}

void Vote_machine::ShowCandidates()
{
    for(auto candidates_it = candidates_votes.begin();
    candidates_it != candidates_votes.end(); ++candidates_it)
    {
        std::cout<<"ShowCandidates";
        // std::cout << candidates_it->first << std::endl;
    }
}

void Vote_machine::ShowStatistics()
{
    std::cout<<"ShowStatistics";
}

void Vote_machine::VoteById(unsigned int vote_id)
{
    //?
}

std::string& Vote_machine::GetVoteMachineDetails() const
{
    // return itoa(m_machine_ip) && itoa(m_machine_port);
}

void Vote_machine::ChangeCandidate(unsigned int vote_id, std::string new_candidate)
{
    // candidates_votes.find(vote_id);
    // then change it...
}
std::unordered_map<unsigned int, Candidate&>& Vote_machine::CandidateVotesInit()
{
    //init?
}

void Vote_machine::MakeCandidate(std::string cadidate_name)
{
    Candidate candidate(cadidate_name);
    std::pair<unsigned int, Candidate&>new_candidate(candidate.GetVoteId(), candidate);
    candidates_votes.insert(new_candidate);
}
}