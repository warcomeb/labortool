#ifndef ACTIVITYNOTE_H
#define ACTIVITYNOTE_H

#include <QString>
#include <QDate>

class ActivityNote
{
public:
    ActivityNote(QString text);

private:
    uint m_id;

    QString m_text;
    QDate   m_registration;
};

#endif // ACTIVITYNOTE_H
