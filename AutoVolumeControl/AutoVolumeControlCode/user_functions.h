#ifndef _USER__
#define _USER__

long UserPrompt();
long UserProfiling();
void SaveUserProfile(int rating);
long CheckIfUserProfileExists();
void RatingSoundText();
long CheckAvgFirstTime();

const int BASIC_BUFFER_SIZE = 256;

#endif /* _USER_ */
