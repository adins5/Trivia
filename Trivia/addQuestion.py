#! /usr/bin/python

import sys
import requests
import sqlite3

data = requests.get('https://opentdb.com/api.php?amount=' + str(sys.argv[1]) + '&category=18&difficulty=medium&type=multiple').json()

con = sqlite3.connect('triviaDB.sqlite')
cur = con.cursor()

roomId = int(sys.argv[2])

# Insert a row of data
for i in range(1, int(str(sys.argv[1])) + 1):
    cur.execute("INSERT INTO QUESTIONS (ID, ROOM_ID, QUESTION) VALUES ({}, {}, \"{}\")".format(i + roomId * 100, roomId, data['results'][i - 1]['question']))
    cur.execute("INSERT INTO ANSWERS (Q_ID, CORR_ANS, ANSWER) VALUES ({}, 1, \"{}\")".format(i + roomId * 100, data['results'][i - 1]['correct_answer']))

    for j in range(3):
        cur.execute("INSERT INTO ANSWERS (Q_ID, CORR_ANS, ANSWER) VALUES ({}, 0, \"{}\")".format(i + roomId * 100, data['results'][i - 1]['incorrect_answers'][j]))

# Save (commit) the changes
con.commit()

# We can also close the connection if we are done with it.
# Just be sure any changes have been committed or they will be lost.
con.close()
