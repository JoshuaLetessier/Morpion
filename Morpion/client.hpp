#pragma once

inline int client();
inline int sendData(const char data[4096]);
inline char* recvData();
static void dataManager();

static const char* importFromMorpion;
static bool end = false;

