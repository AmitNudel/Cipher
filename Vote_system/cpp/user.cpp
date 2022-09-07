#include "libs.hpp"

#include "user.hpp"
#include "vote_machine.hpp"

namespace vote_system
{
User::User(std::string full_name, unsigned int id)
:m_full_name(full_name), m_id(id), m_password(), m_vote_flag(false)
{

}

std::string User::ChooseCandidates(Vote_machine& vote_machine)
{
     //prompt user to write candidates names
     //until when can you insert new candidates?
     std::string candidates; 
     std::cin>>candidates; //don't forget to protect
     //shoul I put one at a time, or a list?
}

void User::ChangeCandidate(Vote_machine& vote_machine, unsigned int candidate_id, std::string new_candidate)
{
    //only at a time it's allowed at
    vote_machine.ChangeCandidate(candidate_id, new_candidate);
}

void User::Vote(Vote_machine& vote_machine, unsigned int candidate_id)
{
    if (false == m_vote_flag)
    {
        vote_machine.VoteById(candidate_id);
        m_vote_flag = true; // how do I lock it?
    }
    else
    {
        std::cout<<"Already voted"<<std::endl; //error? execption? meh?
    }
}

void User::ChangeVote(Vote_machine& vote_machine, unsigned int candidate_id, std::string new_vote)
{
    //only at a time it's allowed at
    m_vote_flag = false;
    vote_machine.VoteById(candidate_id);
}

std::string User::GetFullName() const
{
    return m_full_name;
}

unsigned int User::GetId() const
{
    return m_id;
}

}