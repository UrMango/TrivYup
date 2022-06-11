import requests
import json
import sqlite3



def insertVaribleIntoTable():
    # GET QUESTIONS
    URL = "https://opentdb.com/api.php?amount=50&type=multiple"
    jason_array = requests.get(URL)
    dict_obj = json.loads(jason_array.text)
    #CONNECT TO DB
    sqliteConnection = sqlite3.connect('C:\\shirel\\magshimim\\שנה ב\\קורס עקרונות מתקדמים\\progects\\trivia_shirel_noam_2022\\Trivia\\trivia.sqlite')
    print('Connected to database successfully.')
    cur = sqliteConnection.cursor()

    try:
        for i in range (0, 50):
            # GET one question
            question_obj = dict_obj["results"][i]

            #INSERT QUESTION INTO DATA BASE
            data_tuple = (question_obj["question"], question_obj["correct_answer"], question_obj["incorrect_answers"][0], question_obj["incorrect_answers"][1], question_obj["incorrect_answers"][2])
            string = "insert into QUESTIONS(QUESTION, ANSWER, WRONGANS, WRONGANS1, WRONGANS2) values(?, ?, ?, ?, ?);"
            cur.execute(string, data_tuple)

        # Return all results of query
        #cur.execute('SELECT * from QUESTIONS')
        #print(cur.fetchall())

        sqliteConnection.commit()

    except sqlite3.Error as error:
        print("Failed to insert Python variable into sqlite table", error)
    finally:
        if sqliteConnection:
            # Be sure to close the connection
            sqliteConnection.close()
            print("The SQLite connection is closed")


#insert 4 questions into db
for i in range(0, 8):
    insertVaribleIntoTable() #50 questions
