#define BUFFER_SIZE 512
#define BACKSPACE_KEY 8
#define ENTER_KEY '\r'
#define CLOUD_BUCKET "TestBucket"
#define CLOUD_KEY "TestBlob"

class SampleGame {
 public:
  SampleGame(){};
  ~SampleGame(){};

  int init(const char* appID);
  void gameLoop();

 private:
  bool exitGame = false;
  char commandBuffer[BUFFER_SIZE];
  int commandIndex = 0;

  void checkKeyboard();
  void processCommand();
  void pumpOVRMessages();

  void outputCommands();

  // Command methods
  void getLoggedInUser();
  void getUser(ovrID userID);
  void getLoggedInUserFriends();
  void checkEntitlement();
  void generateUserProof();
  void getUserToken();

  void getAchievementDefinition(char* cheevoName);
  void getAchievementProgress(char* cheevoName);
  void unlockAchievement(char* cheevoName);
  void addAchievementCount(char* cheevoName, char* value);
  void addAchievementBitfield(char* cheevoName, char* value);

  void writeLeaderboardEntry(char* leaderboardName, char* value);
  void getLeaderboardEntries(char* leaderboardName);

  void processGetLoggedInUser(ovrMessageHandle message);
  void processGetUser(ovrMessageHandle message);
  void processGetFriends(ovrMessageHandle message);

  void processCheckEntitlement(ovrMessageHandle message);
  void processGenerateUserProof(ovrMessageHandle message);
  void processGetUserToken(ovrMessageHandle message);

  void processGetAchievementDefinition(ovrMessageHandle message);
  void processGetAchievementProgress(ovrMessageHandle message);
  void processUnlockAchievement(ovrMessageHandle message);
  void processAddAchievementCount(ovrMessageHandle message);
  void processAddAchievementBitfield(ovrMessageHandle message);

  void processWriteLeaderboardEntry(ovrMessageHandle message);
  void processGetLeaderboardEntries(ovrMessageHandle message);

  // Helper methods
  void outputUserArray(ovrUserArrayHandle users);
};
