WTF_CSRF_ENABLED = True                                                                 #make the app more secure
SECRET_KEY = 'admin'                                                                    #needed only if CSRF it's enabled

import os
basedir = os.path.abspath(os.path.dirname(__file__))                                    #define the base path

SQLALCHEMY_DATABASE_URI = 'sqlite:///' + os.path.join(basedir, 'myDB.db')                #path of the DB file !required
SQLALCHEMY_MIGRATE_REPO = os.path.join(basedir, 'db_resposty')                          #where will be stored the migration file