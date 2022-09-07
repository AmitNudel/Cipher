#ifndef __CANDIDATE__
#define __CANDIDATE__

#include "libs.hpp"
namespace vote_system
{
class Candidate
{
public:    
    Candidate(std::string& full_name);
    ~Candidate() = default;
    Candidate(const Candidate& other) = delete;
    Candidate& operator=(const Candidate& other) = delete;

    std::string GetName() const;
    unsigned int GetVotes() const;
    unsigned int GetVoteId() const;
    
    void IncrementVote();//private?
    void DecrementVote();//private?
    
private:
    unsigned int SetVoteId();

    std::string m_full_name;
    unsigned int m_vote_id;
    // unsigned int real_id;
    unsigned int m_vote_count; //do I need another one here?
};
}

#endif //__CANDIDATE__