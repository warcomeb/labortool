#ifndef ACTIVITYNOTE_H
#define ACTIVITYNOTE_H

#include <QString>
#include <QDateTime>

#include "activity.h"
#include "employee.h"

class ActivityNote
{
public:
    ActivityNote(QString text, Activity* activity, Employee* author);
    ActivityNote();

    uint getId () const { return m_id; }
    uint getActivityId () const { return m_activityId; }

    QString getText() const {return m_text; }

    QDateTime getCreationDate () const { return m_creationDate; }
    uint getCreationEmployee () const { return m_creationEmployee; }

    QDateTime getModificationDate () const { return m_modificationDate; }
    uint getModificationEmployee () const { return m_modificationEmployee; }

    void setId (uint id);
    void setActivityId (uint id);

    void setCreationInformation (Employee* author, QDateTime date);
    void setCreationInformation (Employee* author, QString date);

    void setModificationInformation (Employee* author, QDateTime date);
    void setModificationInformation (Employee* author, QString date);

    void setText(QString text);

private:
    uint m_id;

    uint m_activityId;

    QString m_text;

    uint m_creationEmployee;
    uint m_modificationEmployee;

    QDateTime m_creationDate;
    QDateTime m_modificationDate;
};

#endif // ACTIVITYNOTE_H
