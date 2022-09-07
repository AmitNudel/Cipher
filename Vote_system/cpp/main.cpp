#include "candidate.hpp"
#include "vote_machine.hpp"
#include "user.hpp"

#include "alexandria.hpp"


using namespace vote_system;

int BasicCheck()
{
    std::string new_user_name = "Binyamin";
    unsigned int new_user_id = 10;

    User new_user(new_user_name, new_user_id);
    CHECK(); Expect(new_user_name == new_user.GetFullName());
    CHECK(); Expect(new_user_id == new_user.GetId());


    return TEST_PASS;
}

int main()
{
    Run_Test(BasicCheck());
    Is_Success(success);
    return 0;
}