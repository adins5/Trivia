#include "LoggedUser.h"

bool LoggedUser::operator==(LoggedUser other)
{
    return (m_username == other.m_username);
}
