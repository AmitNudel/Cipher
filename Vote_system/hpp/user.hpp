#ifndef __USER__
#define __USER__


#include "libs.hpp"
#include "vote_machine.hpp"

namespace vote_system
{
class User
{
public:
    User(std::string full_name, unsigned int id);
    ~User() = default;
    User(const User& other) = delete;
    User& operator=(const User& other) = delete;

    std::string ChooseCandidates(Vote_machine& vote_machine); //gets the candidates basic info
    void ChangeCandidate(Vote_machine& vote_machine, unsigned int candidate_id, std::string new_candidate);
    void Vote(Vote_machine& vote_machine, unsigned int candidate_id);
    void ChangeVote(Vote_machine& vote_machine, unsigned int candidate_id, std::string new_vote);

    std::string GetFullName() const;
    unsigned int GetId() const;
    
private:
    std::string m_full_name;
    unsigned int m_id;
    std::string m_password;
    bool m_vote_flag;
};
}
#endif //__USER__