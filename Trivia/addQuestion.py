#! /usr/bin/python

import requests
import sqlite3

data = requests.get('https://opentdb.com/api.php?amount=10&category=18&difficulty=medium&type=multiple').json()

con = sqlite3.connect('triviaDB.sqlite')
cur = con.cursor()

# Create table
cur.execute('''CREATE TABLE QUESTIONS(ID INTEGER PRIMARY KEY  NOT NULL, QUESTION TEXT NOT NULL)''')
cur.execute('''CREATE TABLE ANSWERS(ID INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, Q_ID INTEGER NOT NULL, CORR_ANS INTEGER NOT NULL, ANSWER TEXT MOT NULL, FOREIGN KEY(Q_ID) REFERENCES QUESTIONS(ID))''')

# Insert a row of data
for i in range(1, 11):
    cur.execute("INSERT INTO QUESTIONS (ID, QUESTION) VALUES ({}, \"{}\")".format(i, data['results'][i - 1]['question']))
    cur.execute("INSERT INTO ANSWERS (Q_ID, CORR_ANS, ANSWER) VALUES ({}, 1, \"{}\")".format(i, data['results'][i - 1]['correct_answer']))

    for j in range(3):
        cur.execute("INSERT INTO ANSWERS (Q_ID, CORR_ANS, ANSWER) VALUES ({}, 0, \"{}\")".format(i, data['results'][i - 1]['incorrect_answers'][j]))

# Save (commit) the changes
con.commit()

# We can also close the connection if we are done with it.
# Just be sure any changes have been committed or they will be lost.
con.close()
