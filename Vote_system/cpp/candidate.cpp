#include <cstdlib>

#include "candidate.hpp"

namespace vote_system
{

const unsigned int MAX_UNINT = 4294967295;

Candidate::Candidate(std::string& full_name)
:m_full_name(full_name), m_vote_id(SetVoteId()),m_vote_count(0)
{

}
std::string Candidate::GetName() const
{
    return m_full_name;
}

unsigned int Candidate::GetVotes() const
{
    return m_vote_count;
}

void Candidate::IncrementVote()
{
    ++m_vote_count;
}

void Candidate::DecrementVote()
{
    --m_vote_count;
}

unsigned int Candidate::GetVoteId() const
{
    return m_vote_id;
}

unsigned int Candidate::SetVoteId()
{
    unsigned int rand_id = (unsigned int)(rand() % MAX_UNINT);
    return rand_id;
}


}