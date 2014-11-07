#include "activitynote.h"

ActivityNote::ActivityNote(QString text, Activity* activity, Employee* author)
{
    m_id = 0;

    m_activityId = activity->getId();

    m_text = text;

    m_creationEmployee = m_modificationEmployee = author->getId();
    m_creationDate = m_modificationDate = QDateTime::currentDateTime();
}

ActivityNote::ActivityNote()
{
    m_id = 0;
    m_text = "";
}

void ActivityNote::setId (uint id)
{
    m_id = id;
}

void ActivityNote::setActivityId (uint id)
{
    m_activityId = id;
}

void ActivityNote::setCreationInformation (Employee* author, QDateTime date)
{
    m_creationEmployee = author->getId();
    m_creationDate = date;
}

void ActivityNote::setCreationInformation (Employee* author, QString date)
{
    m_creationEmployee = author->getId();
    m_creationDate = QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
}

void ActivityNote::setModificationInformation (Employee* author, QDateTime date)
{
    m_modificationEmployee = author->getId();
    m_modificationDate = date;
}

void ActivityNote::setModificationInformation (Employee* author, QString date)
{
    m_modificationEmployee = author->getId();
    m_modificationDate = QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
}

void ActivityNote::setText(QString text)
{
    m_text = text;
}
