#include "OVR_Platform.h"
#include "SampleGame.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

unsigned char dataBlob[] =
    {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xDE, 0xAD, 0xBE, 0xEF};

int SampleGame::init(const char* appID) {
  if (ovr_PlatformInitializeWindows(appID) != ovrPlatformInitialize_Success) {
    return 1;
  }

  ovr_Entitlement_GetIsViewerEntitled();

  printf("Press h for list of commands.\nCommand > ");

  return 0;
}

void SampleGame::gameLoop() {
  while (!exitGame) {
    checkKeyboard();
    pumpOVRMessages();
  }
}

void SampleGame::checkKeyboard() {
  if (_kbhit()) {
    int key = _getch();

    switch (key) {
      case BACKSPACE_KEY:
        if (commandIndex > 0) {
          commandIndex--;
          commandBuffer[commandIndex] = '\0';
          printf("%c %c", key, key);
        }
        break;
      case ENTER_KEY:
        commandBuffer[commandIndex] = '\0';
        printf("\n");
        processCommand();
        break;

      default:
        if (commandIndex < BUFFER_SIZE) {
          commandBuffer[commandIndex] = key;
          printf("%c", key);
          commandIndex++;
        }
        break;
    }
  }
}

void SampleGame::processCommand() {
  char* command = NULL;
  char* param1 = NULL;
  char* param2 = NULL;
  char* param3 = NULL;

  ovrID param1ID = 0;
  ovrID param2ID = 0;
  ovrID param3ID = 0;

  char* nextToken = NULL;
  char seps[] = " ";

  // Grab the command parameters
  command = strtok_s(commandBuffer, seps, &nextToken);
  param1 = strtok_s(NULL, seps, &nextToken);
  if (param1) {
    param1ID = _strtoui64(param1, NULL, 10);
  }
  param2 = strtok_s(NULL, seps, &nextToken);
  if (param2) {
    param2ID = _strtoui64(param2, NULL, 10);
  }
  param3 = strtok_s(NULL, seps, &nextToken);
  if (param3) {
    param3ID = _strtoui64(param3, NULL, 10);
  }

  if (command) {
    switch (command[0]) {
      case 'h':
        outputCommands();
        break;
      case 'm':
        getLoggedInUser();
        break;
      case 'u':
        if (param1) {
          getUser(param1ID);
        } else {
          printf("Missing Params\n");
        }
        break;
      case 'd':
        getLoggedInUserFriends();
        break;
      case 'e':
        checkEntitlement();
        break;
      case 'n':
        generateUserProof();
        break;
      case 't':
        getUserToken();
        break;
      case 'a':
        if (param1) {
          getAchievementDefinition(param1);
        } else {
          printf("Missing Params\n");
        }
        break;
      case 'b':
        if (param1) {
          getAchievementProgress(param1);
        } else {
          printf("Missing Params\n");
        }
        break;
      case '3':
        if (param1) {
          unlockAchievement(param1);
        } else {
          printf("Missing Params\n");
        }
        break;
      case '4':
        if (param1 && param2) {
          addAchievementCount(param1, param2);
        } else {
          printf("Missing Params\n");
        }
        break;
      case '5':
        if (param1 && param2) {
          addAchievementBitfield(param1, param2);
        } else {
          printf("Missing Params\n");
        }
        break;
      case '1':
        if (param1 && param2) {
          writeLeaderboardEntry(param1, param2);
        } else {
          printf("Missing Params\n");
        }
        break;
      case '2':
        if (param1) {
          getLeaderboardEntries(param1);
        } else {
          printf("Missing Params\n");
        }
        break;
      case 'q':
        exitGame = true;
        break;
      default:
        printf("Invalid Command\n");
        break;
    }

    memset(commandBuffer, 0, sizeof(char) * BUFFER_SIZE);
    commandIndex = 0;
  }

  printf("Command > ");
}

void SampleGame::pumpOVRMessages() {
  ovrMessageHandle message = nullptr;

  while ((message = ovr_PopMessage()) != nullptr) {
    switch (ovr_Message_GetType(message)) {
      case ovrMessage_User_GetLoggedInUser:
        processGetLoggedInUser(message);
        break;
      case ovrMessage_User_Get:
        processGetUser(message);
        break;
      case ovrMessage_User_GetLoggedInUserFriends:
        processGetFriends(message);
        break;
      case ovrMessage_User_GetUserProof:
        processGenerateUserProof(message);
        break;
      case ovrMessage_User_GetAccessToken:
        processGetUserToken(message);
        break;
      case ovrMessage_Achievements_GetDefinitionsByName:
        processGetAchievementDefinition(message);
        break;
      case ovrMessage_Achievements_GetProgressByName:
        processGetAchievementProgress(message);
        break;
      case ovrMessage_Achievements_Unlock:
        processUnlockAchievement(message);
        break;
      case ovrMessage_Achievements_AddCount:
        processAddAchievementCount(message);
        break;
      case ovrMessage_Achievements_AddFields:
        processAddAchievementBitfield(message);
        break;
      case ovrMessage_Leaderboard_WriteEntry:
        processWriteLeaderboardEntry(message);
        break;
      case ovrMessage_Leaderboard_GetEntries:
        processGetLeaderboardEntries(message);
        break;
      case ovrMessage_Entitlement_GetIsViewerEntitled:
        processCheckEntitlement(message);
        break;
      default:
        fprintf(stderr, "unknown message %d", ovr_Message_GetType(message));
    }
    printf("\nCommand > %s", commandBuffer);
    ovr_FreeMessage(message);
  }
}

void SampleGame::outputCommands() {
  printf(
      "\nList of Commands\n----------------\n"
      "h - list commands\n"
      "m - Get logged in user (ovr_User_GetLoggedInUser)\n"
      "u <userid> - Get user (ovr_User_Get)\n"
      "d - Get logged in users friends (ovr_User_GetLoggedInUserFriends)\n"
      "e - check if current user is entitled for this appid\n"
      "n - generate a user nonce for the current user\n"
      "t - generate a user token for the current user\n"
      "a <achievement name> - get achivement definition\n"
      "b <achievement name> - get achievement progress\n"
      "3 <achievement name> - unlock achievement\n"
      "4 <achievement name> <count> add count to achievement\n"
      "5 <achievement name> <fields> add fields to achievement\n"
      "1 <leaderboard name> <value> - write leaderboard entry\n"
      "2 <leaderboard name> - get leaderboard entries\n"
      "q - quit\n\n");
}

void SampleGame::checkEntitlement() {
  printf("\nChecking for an entitlement\n");

  ovrRequest req;

  req = ovr_Entitlement_GetIsViewerEntitled();
}

void SampleGame::processCheckEntitlement(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("User has an entitlement\n");
  } else {
    printf("Could NOT get an entitlement\n");
    exitGame = true;
  }
}

void SampleGame::getLoggedInUser() {
  printf("\nTrying to get logged in user\n");

  ovrRequest req;

  req = ovr_User_GetLoggedInUser();
}

void SampleGame::processGetLoggedInUser(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Received get logged in user success\n");

    ovrUserHandle user = ovr_Message_GetUser(message);
    printf("user %llu %s\n", ovr_User_GetID(user), ovr_User_GetOculusID(user));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received get user failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::getUser(ovrID userID) {
  printf("\nTrying to get user %llu\n", userID);

  ovrRequest req;

  req = ovr_User_Get(userID);
}

void SampleGame::processGetUser(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Received get user success\n");

    ovrUser* user = ovr_Message_GetUser(message);
    printf("user %llu %s\n", ovr_User_GetID(user), ovr_User_GetOculusID(user));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received get user failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::processGetFriends(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Received get friends success\n");

    ovrUserArrayHandle users = ovr_Message_GetUserArray(message);
    outputUserArray(users);
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received get friends failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::getLoggedInUserFriends() {
  printf("\nTrying to get friends for logged in user\n");

  ovrRequest req;

  req = ovr_User_GetLoggedInUserFriends();
}

void SampleGame::outputUserArray(ovrUserArrayHandle users) {
  size_t nUsers = ovr_UserArray_GetSize(users);
  for (size_t i = 0; i < nUsers; ++i) {
    ovrUserHandle user = ovr_UserArray_GetElement(users, i);
    printf(
        "user %llu %s %s\n",
        ovr_User_GetID(user),
        ovr_User_GetOculusID(user),
        ovr_User_GetPresence(user));
  }
}

void SampleGame::generateUserProof() {
  printf("\nTrying to generate a user nonce\n");

  ovrRequest req;

  req = ovr_User_GetUserProof();
}

void SampleGame::processGenerateUserProof(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ovrUserProofHandle proof = ovr_Message_GetUserProof(message);
    printf("Received user nonce %s\n", ovr_UserProof_GetNonce(proof));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received user nonce failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::getUserToken() {
  printf("\nTrying to generate a user token\n");

  ovrRequest req;

  req = ovr_User_GetAccessToken();
}

void SampleGame::processGetUserToken(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Received user token %s\n", ovr_Message_GetString(message));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received user token failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::getAchievementDefinition(char* cheevoName) {
  printf("\nTrying to get definition for achievement %s\n", cheevoName);

  ovrRequest req;

  req = ovr_Achievements_GetDefinitionsByName((const char**)&cheevoName, 1);
}

void SampleGame::processGetAchievementDefinition(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ovrAchievementDefinitionArrayHandle cheevos =
        ovr_Message_GetAchievementDefinitionArray(message);

    if (ovr_AchievementDefinitionArray_GetSize(cheevos) > 0) {
      ovrAchievementDefinitionHandle singleCheevo =
          ovr_AchievementDefinitionArray_GetElement(cheevos, 0);

      printf(
          "Received get achievement definition for %s\n",
          ovr_AchievementDefinition_GetName(singleCheevo));

      switch (ovr_AchievementDefinition_GetType(singleCheevo)) {
        case ovrAchievement_TypeSimple:
          printf("Type: Simple\n");
          break;

        case ovrAchievement_TypeBitfield:
          printf("Type: Bitfield\n");
          printf(
              "Bitfield Length: %d\n", ovr_AchievementDefinition_GetBitfieldLength(singleCheevo));
          printf("Cheevo Target: %llu\n", ovr_AchievementDefinition_GetTarget(singleCheevo));
          break;

        case ovrAchievement_TypeCount:
          printf("Type: Count\n");
          printf("Cheevo Target: %llu\n", ovr_AchievementDefinition_GetTarget(singleCheevo));
          break;

        case ovrAchievement_TypeUnknown:
        default:
          printf("Type: Unknown\n");
          break;
      }
    } else {
      printf("Achievement not found\n");
    }
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received get achievement definition failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::getAchievementProgress(char* cheevoName) {
  printf("\nTrying to get progress for achievement %s\n", cheevoName);

  ovrRequest req;

  req = ovr_Achievements_GetProgressByName((const char**)&cheevoName, 1);
}

void SampleGame::processGetAchievementProgress(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ovrAchievementProgressArrayHandle cheevos = ovr_Message_GetAchievementProgressArray(message);
    if (ovr_AchievementProgressArray_GetSize(cheevos) > 0) {
      ovrAchievementProgressHandle singleCheevo =
          ovr_AchievementProgressArray_GetElement(cheevos, 0);

      printf(
          "Received get achievement progress for %s\n",
          ovr_AchievementProgress_GetName(singleCheevo));

      if (ovr_AchievementProgress_GetIsUnlocked(singleCheevo)) {
        printf("Cheevo is currently unlocked\n");
        printf("Cheevo was unlocked at %llu\n", ovr_AchievementProgress_GetUnlockTime(singleCheevo));
      } else {
        printf("Cheevo is NOT currently unlocked\n");
      }

      const char* bitField = ovr_AchievementProgress_GetBitfield(singleCheevo);
      unsigned long long count = ovr_AchievementProgress_GetCount(singleCheevo);

      printf("Current Progress: bitfield: %s count: %llu\n", bitField, count);

    } else {
      printf("No progress to report.\n");
    }
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received get achievement progress failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::unlockAchievement(char* cheevoName) {
  printf("\nTrying to unlock achievement %s\n", cheevoName);

  ovrRequest req;

  req = ovr_Achievements_Unlock((const char*)cheevoName);
}

void SampleGame::processUnlockAchievement(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Cheevo is now unlocked\n");
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received unlock achievement failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::addAchievementCount(char* cheevoName, char* value) {
  printf("\nTrying to add %lld to achievement %s\n", _atoi64(value), cheevoName);

  ovrRequest req;

  req = ovr_Achievements_AddCount((const char*)cheevoName, _atoi64(value));
}

void SampleGame::processAddAchievementCount(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Cheevo count added.\n");
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received add count achievement failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::addAchievementBitfield(char* cheevoName, char* value) {
  printf("\nTrying to add %s to achievement %s\n", value, cheevoName);

  ovrRequest req;

  req = ovr_Achievements_AddFields((const char*)cheevoName, (const char*)value);
}

void SampleGame::processAddAchievementBitfield(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Cheevo field added.\n");
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received add field achievement failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::writeLeaderboardEntry(char* leaderboardName, char* value) {
  printf("\nTrying to write leaderboard entry to  %s\n", leaderboardName);

  ovrRequest req;

  char DummyData[]{'T', 'e', 's', 't'};
  req = ovr_Leaderboard_WriteEntry(
      leaderboardName, _atoi64(value), &DummyData, sizeof(DummyData), false);
}

void SampleGame::processWriteLeaderboardEntry(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ovrLeaderboardUpdateStatusHandle updateResult = ovr_Message_GetLeaderboardUpdateStatus(message);
    if (ovr_LeaderboardUpdateStatus_GetDidUpdate(updateResult)) {
      printf("Leaderboard entry was updated.\n");
    } else {
      printf("Leaderboard entry was NOT updated.\n");
    }
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received leaderboard write failure: %s\n", ovr_Error_GetMessage(error));
  }
}

void SampleGame::getLeaderboardEntries(char* leaderboardName) {
  printf("\nTrying to get leaderboard entries for  %s\n", leaderboardName);

  ovrRequest req;

  req = ovr_Leaderboard_GetEntries(
      leaderboardName,
      10 /* limit to return */,
      ovrLeaderboard_FilterNone,
      ovrLeaderboard_StartAtTop);
}

void SampleGame::processGetLeaderboardEntries(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ovrLeaderboardEntryArrayHandle results = ovr_Message_GetLeaderboardEntryArray(message);

    unsigned long long totalRows = ovr_LeaderboardEntryArray_GetTotalCount(results);

    size_t count = ovr_LeaderboardEntryArray_GetSize(results);

    printf("Total Rows in Leaderboard: %llu\n", totalRows);

    for (size_t x = 0; x < count; x++) {
      ovrLeaderboardEntryHandle entry = ovr_LeaderboardEntryArray_GetElement(results, x);

      ovrUserHandle user = ovr_LeaderboardEntry_GetUser(entry);
      long long score = ovr_LeaderboardEntry_GetScore(entry);
      unsigned int ranking = ovr_LeaderboardEntry_GetRank(entry);
      const char* extraData = ovr_LeaderboardEntry_GetExtraData(entry);
      unsigned long long timestamp = ovr_LeaderboardEntry_GetTimestamp(entry);

      printf(
          "%d. %s %llu %s %llu\n",
          ranking,
          ovr_User_GetOculusID(user),
          score,
          extraData,
          timestamp);
    }
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received leaderboard fetch failure: %s\n", ovr_Error_GetMessage(error));
  }
}
