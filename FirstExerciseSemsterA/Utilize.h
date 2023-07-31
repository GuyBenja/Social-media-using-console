#ifndef UTILIZE_H
#define UTILIZE_H
#include <unordered_map>
#include <string>
#include "User.h"
#include "FanPage.h"
#include "Date.h"
#include "Exceptions.h"

void readName(std::string& name) throw(NameException);
void cleanBuffer();
const Date& readDate();
void readStatusForUser(std::unordered_map<std::string, User*>& users, const std::string& userName) throw(UnrecognizeCharException, UserException);
void readStatusForFanPage(std::unordered_map<std::string, FanPage*>& pages, const std::string& name) throw(UnrecognizeCharException, FanPageException);




#endif // !UTILIZE_H
